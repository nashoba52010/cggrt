#pragma once

#include "fwd.h"
#include "tensor.h"
#include <assert.h>
#include <stddef.h>

typedef int cggrt_Node_state_t;

#define CGGRT_NODE_ST_NULL (0)    // Node not allocated
#define CGGRT_NODE_ST_INVALID (1) // Node allocated but value not computed
#define CGGRT_NODE_ST_VALID (2)   // Node allocated and computed
#define CGGRT_NODE_MAX_OPS (1024)

// TODO: Use dynamic instead of static with limit
#define CGGRT_NODE_MAX_SUCCS (64)

#define CGGRT_NODE_HEADER                                                      \
  cggrt_Node_op_t op;                                                          \
  cggrt_Node_state_t state;                                                    \
  cggrt_Tensor result;                                                         \
                                                                               \
  size_t succs_count;                                                          \
  cggrt_Node *succs[CGGRT_NODE_MAX_SUCCS];                                     \
                                                                               \
  size_t preds_count;                                                          \
  cggrt_Node *preds[0];

struct S_cggrt_Node {
  CGGRT_NODE_HEADER
  // Node attributes are stored inside the node subclass
};

// fdyn table for Node
typedef void (*cggrt_Node_fdyn_exec_f)(cggrt_Node *);
extern const cggrt_Node_fdyn_exec_f
    cggrt_Node_fdyn_table_exec[CGGRT_NODE_MAX_OPS];

// internal, create unitialized node
// called by constructors of special node instances
cggrt_Node *cggrt_Node_new(size_t struct_size);

// internal, only called by graph class
void cggrt_Node_free(cggrt_Node *node);

static inline size_t cggrt_Node_preds_count(cggrt_Node *node) {
  return node->preds_count;
}

static inline cggrt_Node *cggrt_Node_pred(cggrt_Node *node, size_t i) {
  assert(i < node->preds_count);
  return node->preds[i];
}

static inline size_t cggrt_Node_succs_count(cggrt_Node *node) {
  return node->succs_count;
}

static inline cggrt_Node *cggrt_Node_succ(cggrt_Node *node, size_t i) {
  assert(i < node->preds_count);
  return node->succs[i];
}
