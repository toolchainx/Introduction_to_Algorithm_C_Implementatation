#ifndef _BFS_H_
#define _BFS_H_

#include "adj_table.h"
#include "stack.h"

// 实现邻接链表的广度优先搜索
AdjList* bfs(AdjList* pAdjl, int numVertices, int org_vertex, int* distance, int* parent);
void print_path(AdjList* pAdjl, int numVertices, int* parent, int start, int end);

EBool peek(Stack s, int idx, int *pv);
EBool calc_path(AdjList* graph, int numVertices, int* parent, int s, int t, Stack path);

#endif /* _BFS_H_ */
