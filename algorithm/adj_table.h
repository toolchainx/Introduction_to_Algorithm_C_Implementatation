#ifndef _ADJ_TABLE_H_
#define _ADJ_TABLE_H_

#include "include/require.h"
#define ALLOC_SIZE 10
#define INCREMENT_SIZE 5
typedef enum {WHITE, GRAY, BLACK}EColor;
typedef enum {TREE, BACK, FORWARD, CROSS}EEdge;

typedef struct tag_adjList
{
    int vertex;
    int weight;
    EEdge edgeType;
    struct tag_adjList * next;
}AdjListNode, *AdjList, *AdjListNodePtr;

// declaraion of the functions
// insert a node its value is `value`
// return: the list of the adj_list
AdjList adj_insert(AdjList adjl, int value);

// 创建并插入一个带有权重的结点
AdjList adj_weight_insert(AdjListNodePtr adjpnode, int value, int weight);

AdjList* construct_weighted_adjlist(const char* filename, AdjList*
                                      adjList, int* pnumVertices);

// 释放邻接链表
void free_adjlist(AdjList adjl[], int count);

// 增加数组的长度
AdjList* arr_realloc(AdjList* adjList, int* parrLength);

// 输出邻接链表
void print_adjlist(AdjList adjlist[], int length);

AdjList* construct_adjlist(const char* filename, AdjList* pAdjl, int* numVertices);
#endif /* _ADJ_TABLE_H_ */

AdjList* copy_adjlist(AdjList* graph, int numVertices);

EBool add_edge(AdjList* graph, int numVertices, int u, int v);
EBool del_edge(AdjList* graph, int numVertices, int u, int v);
