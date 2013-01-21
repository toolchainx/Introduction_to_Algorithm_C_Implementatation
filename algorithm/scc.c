// To be modified 待修改， 之前的依赖发生了改变
// 已知图的结构，找出强连通分支
// 先深度优先搜索，得到每个顶点的完成时间，对顶点的完成时间进行拓扑排序
// 计算图的转置图
// 按照前面在深度优先搜索中完成时间的降序，对转置图进行深度优先搜索，
// 依次访问每个顶点，得到图的强连通分支
#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"
#include "list.h"
#include "adj_table.h"
#include "transpose_adj_table.h"

extern int Time;
extern List list;
extern int parent[];
extern Color color[];
extern int d[];
extern int f[];


void transpose_dfs(adj_list* graph, int numVertices, List lst)
{
    int i;
    // 对数据结构进行初始化操作
    Time = 0;
    for (i = 0; i < ALLOC_SIZE; i++) {
	color[i] = WHITE;
	parent[i] = NIL;
	d[i] = 0;
	f[i] = 0;
    }
    while (lst) {
	if(color[lst->value] == WHITE)
	{
	    dfs_visit(lst->value, graph, numVertices);
	    printf("--------------------\n");
	}
	lst = lst->next;    
    }
    // 注意边界条件，初始化操作和结束操作
}
// 函数接口的设计
// 输入：adj_list* graph，list用于拓扑排序
// 输出：能否输出分支图？ 打印出所有强连通分支的顶点
// 改变的值： graph，在转置的过程中使graph转变成graph_tanspose
void scc(adj_list* graph, int numVertices)
{
    // 深度优先搜索，同时对其进行拓扑排序，排序的结果保存在list中
    dfs(graph, numVertices);
    // 转置
    graph = transpose_adj_table(graph, numVertices);
    printf("the transposed graph\n");
    adj_output(graph, numVertices);
    // 根据拓扑排序和转置的结果进行深度优先搜索
    transpose_dfs(graph, numVertices, list);
    
}

int main(int argc, char *argv[])
{
    adj_list* pAdjl = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("%s filename\n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // 构建图
    pAdjl = construct_adj_list(argv[1], pAdjl, &numVertices);
    // 对数据的输出进行测试，如何测试？
    //
    scc(pAdjl, numVertices);
    print_list(list);    
    return 0;
}
