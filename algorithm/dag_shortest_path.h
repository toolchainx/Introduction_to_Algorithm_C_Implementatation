#ifndef _DAG_SHORTEST_PATH_H_
#define _DAG_SHORTEST_PATH_H_

#include "include/require.h"
#include "single_source_shortest_path.h"
#include "toplogical_sort.h"
#include "adj_table.h"

void dag_shortest_path(adj_list* graph, int length, int s, int d[], int parent[]);

#endif /* _DAG_SHORTEST_PATH_H_ */
