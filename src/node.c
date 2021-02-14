#include <cggrt/node.h>
#include <cggrt/tensor.h>

#include <stdlib.h>

#include "gen/nodes-fdyn.c"

cggrt_Node *cggrt_Node_new(size_t struct_size) {
  return (cggrt_Node *)malloc(struct_size);
}

// internal, only called by graph class
void cggrt_Node_free(cggrt_Node *node) {
  cggrt_Tensor_free(&node->result);
  free(node);
}
