#include <stdio.h>
#include <stdlib.h>
#include "toplogical_sort.h"




EBool toplogical_sort(AdjList* graph, int numVertices, List* sortedListPtr)
{
    // 分配数组，保存先辈子图parent[]，探测时间d[]，完成时间f[]
    int i, j, min;
    int *parent, *d, *f, *topSortArray;
    if (graph == NULL)
    {
	printf("invalid graph\n");
	exit(EXIT_FAILURE);
    }
    parent = (int *)malloc(numVertices * sizeof(int));
    d = (int *)malloc(numVertices * sizeof(int));
    f = (int *)malloc(numVertices * sizeof(int));
    topSortArray = (int *)malloc(numVertices * sizeof(int));
    for (i = 0; i < numVertices; i++) {
	topSortArray[i] = i;
    }

    dfs(graph, numVertices, parent, d, f, NULL);
    // 对数据的输出进行测试，如何测试？
    // 通过利用完成时间f[]来获得拓扑排序
    // 思考，如何按照数组中元素的值对数组中的索引进行排序?
    printf("\n");
    print_array("f", f, numVertices);
    for (i = 0; i < numVertices-1; i++) {
	min = i;
	for (j = i+1; j < numVertices; j++) {
	    if (f[min] > f[j])
	    {
	        min = j;
	    }
	}
	array_swap(f, i, min);
	array_swap(topSortArray, i, min);
    }
    printf("\n");
    print_array("f", f, numVertices);
    print_array("topSortArray", topSortArray, numVertices);
    for (i = 0; i < numVertices; i++) {
	*sortedListPtr = list_insert(*sortedListPtr, topSortArray[i]);
    }
    free(topSortArray);
    free(f);
    free(d);
    free(parent);    
    return 0;
}
