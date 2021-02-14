#include <cggrt/graph.h>
#include <cggrt/node.h>

#include <assert.h>
#include <stdlib.h>

// @[TODO] use a dynamic way to add nodes
#define GRAPH_MAX_NODES (4096)

struct S_cggrt_Graph {
  cggrt_Node *nodes[GRAPH_MAX_NODES];
  size_t nodes_count;
};

cggrt_Graph *cggrt_Graph_new() {
  cggrt_Graph *g = malloc(sizeof(cggrt_Graph));
  g->nodes_count = 0;
  return g;
}

void cggrt_Graph_free(cggrt_Graph *g) {
  for (size_t i = 0; i < g->nodes_count; ++i)
    if (g->nodes[i])
      cggrt_Node_free(g->nodes[i]);
  free(g);
}

void cggrt_Graph_finish_add(cggrt_Graph *g, cggrt_Node *node) {
  node->succs_count = 0;

  g->nodes[g->nodes_count++] = node;

  for (size_t i = 0; i < node->preds_count; ++i) {
    cggrt_Node *pred = node->preds[i];
    pred->succs[pred->succs_count++] = node;
  }
}

static void exec_node(cggrt_Node *node) {
  // Check if can be executed
  assert(node->state != CGGRT_NODE_ST_NULL);
  if (node->state == CGGRT_NODE_ST_VALID) // already computed
    return;

  // exec preds
  for (size_t i = 0; i < node->preds_count; ++i)
    exec_node(node->preds[i]);

  // run computation
  cggrt_Node_fdyn_exec_f fun = cggrt_Node_fdyn_table_exec[node->op];
  assert(fun);
  fun(node);

  node->state = CGGRT_NODE_ST_VALID;
}

void cggtr_Graph_run(cggrt_Graph *g, cggrt_Node **targets,
                     size_t targets_count) {
  (void)g;
  for (size_t i = 0; i < targets_count; ++i)
    exec_node(targets[i]);
}
