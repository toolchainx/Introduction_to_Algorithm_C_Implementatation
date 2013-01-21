#include <stdio.h>
#include <stdlib.h>
#include "dag_shortest_path.h"

int main(int argc, char *argv[])
{
    adj_list* graph = NULL;
    int length;
    int i;
    int s;
    int* d;
    int* parent;
    // 构造邻接链表
    if (argc != 3)
    {
	printf("usage: %s data_filename source_vertex\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    sscanf(argv[2], "%d", &s);
    graph = construct_weighted_adj_list(argv[1], graph, &length);
    // 根据邻接链表的长度分配最短路径估计d和前驱数组parent
    d = (int *)malloc(length * sizeof(int));
    parent = (int *)malloc(length * sizeof(int));
    dag_shortest_path(graph, length, s, d, parent);
    // 打印输出顶点s到各顶点的最短路径的结果
    for (i = 0; i < length; i++) {
	print_path(graph, parent, s, i);
	printf("\n");
    }
    array_print(parent, length);
    free(parent);
    free(d);
    return 0;
}

