#ifndef _DFS_H_
#define _DFS_H_
#include "adj_table.h"
#include "include/require.h"


EBool dfs_visit(int i, adj_list* graph, int numVertices, Color* color, int* parent, int* d, int* f);
// 假定graph parent, d, f的内存已分配好
EBool dfs(adj_list* graph, int numVertices, int *parent, int* d, int* f);

void print_edgetype(int start, int end, int type);
void print_array(const char* arr_name, int arr[], int length);



#endif /* _DFS_H_ */
