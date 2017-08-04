cmake_minimum_required(VERSION 3.8)
project(aMeshClass)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp src/mesh.cpp src/mesh.h)
add_executable(aMeshClass ${SOURCE_FILES})