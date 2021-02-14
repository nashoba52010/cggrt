#pragma once

#include "fwd.h"
#include "node.h"
#include "shape.h"
#include "types.h"

struct S_cggrt_NodeConstAttrs {
  void *data;        // pointer to const data
  cggrt_Shape shape; // data shape
  cggrt_data_t dt;
};

struct S_cggrt_NodeConst {
  CGGRT_NODE_HEADER
  cggrt_NodeConstAttrs attrs;
};

cggrt_NodeConst *cggrt_Graph_op_const(cggrt_Graph *g,
                                      cggrt_NodeConstAttrs attrs);

// Dispatch function called to exec node
void cggrt_NodeConst_fdyn_exec(cggrt_Node *node);
