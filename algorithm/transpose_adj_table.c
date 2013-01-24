// 将一个临界表转置
#include <stdio.h>
#include <stdlib.h>
#include "transpose_adj_table.h"

//函数接口的设计
// 输入：adj_list* G
// 输出：adj_list* G_tanspose
// 改变的对象：G
AdjList* transpose_adj_table(AdjList* graph, int numVertices)
{
    // 为转置图分配存储空间，并初始化为0
    AdjList* graph_transpose = (AdjList *)calloc(numVertices, sizeof(AdjListNodePtr));
    int i;
    AdjListNodePtr pNode = NULL;
    for (i = 0; i < numVertices; i++) {
	while (graph[i]) {
	    int vertex;
	    // 将结点从graph[i]中取出来
	    // 插入在graph_transpose[i]的前面
	    pNode = graph[i];
	    graph[i] = graph[i]->next;
	    pNode->next = NULL;
	    vertex = pNode->vertex;
	    pNode->vertex = i;
	    pNode->next = graph_transpose[vertex];
	    graph_transpose[vertex] = pNode;
	}
    }
    free(graph);
    return graph_transpose;
}

