// 将一个临界表转置
#include <stdio.h>
#include <stdlib.h>
#include "transpose_adj_table.h"

//函数接口的设计
// 输入：adj_list* G
// 输出：adj_list* G_tanspose
// 改变的对象：G
adj_list* transpose_adj_table(adj_list* graph, int numVertices)
{
    // 为转置图分配存储空间，并初始化为0
    adj_list* graph_transpose = (adj_list *)calloc(numVertices, sizeof(adj_pnode));
    int i;
    adj_pnode pNode = NULL;
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
    freeAdjList(graph, numVertices);
    return graph_transpose;
}

/* int main(int argc, char *argv[]) */
/* { */
/*     adj_list* pAdjl = NULL; */
/*     int numVertices; */
/*     if (argc != 2) */
/*     { */
/* 	printf("input the data file\n"); */
/* 	exit(EXIT_FAILURE); */
/*     } */
/*     pAdjl =  construct_adj_list(argv[1], pAdjl, &numVertices); */
/*     pAdjl = transpose_adj_table(pAdjl, numVertices); */
/*     adj_output(pAdjl, numVertices); */
/*     freeAdjList(pAdjl, numVertices); */
/*     return 0; */
/* } */
