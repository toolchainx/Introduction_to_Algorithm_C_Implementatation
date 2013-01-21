#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"



int main(int argc, char *argv[])
{
    adj_list* graph = NULL;
    int numVertices;
    // 分配数组，保存先辈子图parent[]，探测时间d[]，完成时间f[]
    int *parent, *d, *f;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // 构建图
    graph = construct_adj_list(argv[1], graph, &numVertices);
    parent = (int *)malloc(numVertices * sizeof(int));
    d = (int *)malloc(numVertices * sizeof(int));
    f = (int *)malloc(numVertices * sizeof(int));
    dfs(graph, numVertices, parent, d, f);
    // 对数据的输出进行测试，如何测试？
    // 通过利用完成时间f[]来获得拓扑排序的时间
    return 0;
}
