#ifndef _ADJ_TABLE_H_
#define _ADJ_TABLE_H_

#include "include/require.h"
#define ALLOC_SIZE 10
#define INCREMENT_SIZE 5
typedef enum {WHITE, GRAY, BLACK}Color;
typedef enum {TREE, BACK, FORWARD, CROSS}Edge;

typedef struct tag_adjList
{
    int vertex;
    int weight;
    Edge edgeType;
    struct tag_adjList * next;
}adj_node, *adj_list, *adj_pnode;

// declaraion of the functions
// insert a node its value is `value`
// return: the list of the adj_list
adj_list adj_insert(adj_list adjl, int value);

// 创建并插入一个带有权重的结点
adj_list adj_weight_insert(adj_pnode adjpnode, int value, int weight);

adj_list* construct_weighted_adj_list(const char* filename, adj_list*
                                      adjList, int* pnumVertices);

// 释放邻接链表
void freeAdjList(adj_list adjl[], int count);

// 增加数组的长度
adj_list* arrRealloc(adj_list* adjList, int* parrLength);

// 输出邻接链表
void adj_output(adj_list adjlist[], int length);

adj_list* construct_adj_list(const char* filename, adj_list* pAdjl, int* numVertices);
#endif /* _ADJ_TABLE_H_ */

adj_list* copy_adjlist(adj_list* graph, int numVertices);

EBool add_edge(adj_list* graph, int numVertices, int u, int v);
EBool del_edge(adj_list* graph, int numVertices, int u, int v);
