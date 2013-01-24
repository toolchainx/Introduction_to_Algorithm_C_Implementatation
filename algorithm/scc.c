// To be modified 待修改， 之前的依赖发生了改变
// 已知图的结构，找出强连通分支
// 先深度优先搜索，得到每个顶点的完成时间，对顶点的完成时间进行拓扑排序
// 计算图的转置图
// 按照前面在深度优先搜索中完成时间的降序，对转置图进行深度优先搜索，
// 依次访问每个顶点，得到图的强连通分支
#include <stdio.h>
#include <stdlib.h>
#include "include/require.h"
#include "sort_arr_idx.h"
#include "dfs.h"
#include "list.h"
#include "adj_table.h"
#include "transpose_adj_table.h"

// 函数接口的设计
// 输入：adj_list* graph，list用于拓扑排序
// 输出：能否输出分支图？ 打印出所有强连通分支的顶点
// 改变的值： graph，在转置的过程中使graph转变成graph_tanspose
void scc(AdjList* graph, int numVertices)
{
    int *parent, *d, *f, *seq;
    parent = (int *)malloc(numVertices * sizeof(int));
    d = (int *)malloc(numVertices * sizeof(int));
    f = (int *)malloc(numVertices * sizeof(int));
    seq = (int *)malloc(numVertices * sizeof(int));
    // 深度优先搜索，同时对其进行拓扑排序，排序的结果保存在list中
    dfs(graph, numVertices, parent, d, f, NULL);
    // sort the index of f by its value
    printf("f: \n");
    array_print(f, numVertices);
    sort_arr_idx(f, numVertices, seq);
    rvs_arr(seq, numVertices);
    printf("seq: \n");
    array_print(seq, numVertices);
    // 转置
    graph = transpose_adj_table(graph, numVertices);
    printf("the transposed graph\n");
    print_adjlist(graph, numVertices);
    // 根据拓扑排序和转置的结果进行深度优先搜索
    dfs(graph, numVertices, parent, d, f, seq);
    free(parent);
    free(d);
    free(f);
    free(seq);
}

int main(int argc, char *argv[])
{
    AdjList* pAdjl = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // 构建图
    pAdjl = construct_adjlist(argv[1], pAdjl, &numVertices);
    // 对数据的输出进行测试，如何测试？
    scc(pAdjl, numVertices);
    return 0;
}
