#ifndef _BFS_H_
#define _BFS_H_

// 实现邻接链表的广度优先搜索
adj_list* bfs(adj_list* pAdjl, int numVertices, int org_vertex, int* distance, int* parent);
void print_path(adj_list* pAdjl, int numVertices, int* parent, int start, int end);

EBool peek(Stack s, int idx, int *pv);
EBool calc_path(adj_list* graph, int numVertices, int* parent, int s, int t, Stack path);

#endif /* _BFS_H_ */
