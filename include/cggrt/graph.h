#pragma once

#include "fwd.h"
#include <stddef.h>

cggrt_Graph *cggrt_Graph_new();

void cggrt_Graph_free(cggrt_Graph *g);

// internal function
// add a new node to the graph
// preds is already set, it'll just update succs on the right nodes
void cggrt_Graph_finish_add(cggrt_Graph *g, cggrt_Node *node);

// Compute all nodes in targets array
// Only compute not computed / unchanged nodes
void cggtr_Graph_run(cggrt_Graph *g, cggrt_Node **targets,
                     size_t targets_count);
