#include <cggrt/graph.h>
#include <cggrt/node-op-const.h>
#include <cggrt/tensor.h>
#include <stdlib.h>

static inline void exec_const(cggrt_Tensor *o_res,
                              cggrt_NodeConstAttrs *attrs) {
  cggrt_Tensor_write(o_res, attrs->data);
}

cggrt_NodeConst *cggrt_Graph_op_const(cggrt_Graph *g,
                                      cggrt_NodeConstAttrs attrs) {
  // Check node
  assert(attrs.dt != CGGRT_DT_UNK && attrs.dt != CGGRT_DT_NULL);
  assert(attrs.shape.count != CGGRT_SHAPE_COUNT_UNDEF);

  cggrt_NodeConst *node =
      (cggrt_NodeConst *)cggrt_Node_new(sizeof(cggrt_NodeConst));
  node->op = CGGRT_NODE_OP_CONST;
  node->state = CGGRT_NODE_ST_INVALID;
  node->preds_count = 0;
  node->attrs = attrs;

  node->result = cggrt_Tensor_new(node->attrs.dt, node->attrs.shape);

  cggrt_Graph_finish_add(g, (cggrt_Node *)node);
  return node;
}

void cggrt_NodeConst_fdyn_exec(cggrt_Node *node) {
  cggrt_NodeConst *n = (cggrt_NodeConst *)node;
  exec_const(&node->result, &n->attrs);
}
