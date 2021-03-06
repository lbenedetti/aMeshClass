//==============================================================================
//
//                                  InsideLoop
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.txt for details.
//
//==============================================================================

#ifndef IL_ALLOCATE_H
#define IL_ALLOCATE_H

// <cstdlib> is used for std::malloc
#include <cstdlib>

#include <il/core/math/safe_arithmetic.h>

namespace il {

template <typename T>
T* allocate_array(il::int_t n) {
  IL_EXPECT_FAST(n >= 0);

  bool error = false;
  const std::size_t n_unsigned = static_cast<std::size_t>(n);
  const std::size_t n_bytes =
      il::safe_product(n_unsigned, sizeof(T), il::io, error);
  if (error) {
    il::abort();
  }

  T* p = static_cast<T*>(std::malloc(n_bytes));
  if (!p && n_bytes > 0) {
    il::abort();
  }

  return p;
}

template <typename T>
T* allocate_array(il::int_t n, il::int_t align_r, il::int_t align_mod, il::io_t,
                  il::int_t& shift) {
  IL_EXPECT_FAST(sizeof(T) == alignof(T));
  IL_EXPECT_FAST(n >= 0);
  IL_EXPECT_FAST(align_mod > 0);
  IL_EXPECT_FAST(align_mod % alignof(T) == 0);
  IL_EXPECT_FAST(align_r >= 0);
  IL_EXPECT_FAST(align_r < align_mod);
  IL_EXPECT_FAST(align_r % alignof(T) == 0);

  const std::size_t n_unsigned = static_cast<std::size_t>(n);
  const std::size_t align_mod_unsigned = static_cast<std::size_t>(align_mod);

  bool product_error = false;
  bool sum_error = false;
  const std::size_t n_bytes = il::safe_sum(
      il::safe_product(n_unsigned, sizeof(T), il::io, product_error),
      align_mod_unsigned - 1, il::io, sum_error);
  if (product_error || sum_error) {
    il::abort();
  }

  T* p = static_cast<T*>(std::malloc(n_bytes));
  if (!p && n_bytes > 0) {
    il::abort();
  }
  const std::size_t align_r_unsigned = static_cast<std::size_t>(align_r);
  const std::size_t p_int = reinterpret_cast<std::size_t>(p);
  const std::size_t r = p_int % align_mod_unsigned;
  const std::size_t local_shift =
      align_r_unsigned >= r
          ? (align_r_unsigned - r) / sizeof(T)
          : (align_mod_unsigned - (r - align_r_unsigned)) / sizeof(T);

  IL_ENSURE(local_shift < static_cast<std::size_t>(align_mod));

  shift = static_cast<il::int_t>(local_shift);
  T* aligned_p = p + local_shift;
  return aligned_p;
}

inline void deallocate(void* p) { std::free(p); }
}

#endif  // IL_ALLOCATE_H
