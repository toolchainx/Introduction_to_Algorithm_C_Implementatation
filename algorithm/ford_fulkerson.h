#ifndef _FORD_FULKERSON_H_
#define _FORD_FULKERSON_H_
#include <assert.h>
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "include/require.h"
#include "stack.h"
#include "queue.h"
#include "adj_table.h"
#include "adj_mat.h"
#include "bfs.h"

void initialize_edge_flow(adj_list* graph, int numVertices, AdjMat* flow);
void initialize_edge_flow(adj_list* graph, int numVertices, AdjMat* flow);
EBool find_shortest_path(adj_list* graph, int numVertices, int s, int t, Stack path);
int rc(int u, int v, AdjMat* f, AdjMat* c);
int min_res_cap(AdjMat* c, AdjMat* f, Stack path);
void update_flow(AdjMat* f, Stack path, int cfp);
void ford_fulkerson(adj_list* graph, int numVertices, int s, int t, AdjMat* f, AdjMat* c);

#endif /* _FORD_FULKERSON_H_ */
