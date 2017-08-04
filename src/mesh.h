//
// Created by lorenzo on 8/4/17.
//

#ifndef AMESHCLASS_MESH_H
#define AMESHCLASS_MESH_H


// classical approach: allocate all elements in a non-contiguous way

// Define a node class
class node {

private:
  double x_;
  double y_;
  double z_;

public:
  // create node
  // set node
  // get node values


};

class mesh {


};

// a better approach: use a contiguous aligned and expandable class by considering
// all nodes together in a structure/class of arrays and a percentage (default:10%)
// of additional space for future refinement

class meshNodes {

private:


};


#endif //AMESHCLASS_MESH_H
