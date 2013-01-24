#include <stdio.h>
#include <stdlib.h>
#include "toplogical_sort.h"

int main(int argc, char *argv[])
{
    
    List list = NULL;
    AdjList* graph = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    // 构建图
    graph = construct_adjlist(argv[1], graph, &numVertices);
    // 排序的结果为sort_arr的顶点序列按完成时间从大到小进行排序
    toplogical_sort(graph, numVertices, &list);
    print_list(list);
    free_list(list);
    return 0;
}
