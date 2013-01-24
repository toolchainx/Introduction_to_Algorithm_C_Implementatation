#ifndef _JOHNSON_H_
#define _JOHNSON_H_
#include "include/require.h"
#include "adj_table.h"
// used to return the matrix of the shortest path
#include "adj_mat.h"
// bellman_ford algorithm
#include "single_source_shortest_path.h" 
#include "dijkstra.h"

AdjMat* johnson(AdjList* graph, int numVertices);


#endif /* _JOHNSON_H_ */
