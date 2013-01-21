// 有向无回路图的单源最短路径
// 先进行拓扑排序
// 拓扑排序要用到深度优先搜索dfs
// 最后利用链表保存拓扑排序的结果，按完成时间递降的顺序排列
// 根据拓扑排序后的顺序，对以各顶点为起点的边进行松弛


#include <stdio.h>
#include <stdlib.h>
#include "dag_shortest_path.h"

void dag_shortest_path(adj_list* graph, int length, int s, int d[], int parent[])
{
    adj_pnode adjNode;
    List list = NULL, x = NULL;
    // toplogically sort the vertices of G
    toplogical_sort(graph, length, &list);
    initialize_single_source(graph, length, s, d, parent);
    x = list;
    while(x->value != s){
	x = x->next;
    }
    while(x)
    {
	adjNode = graph[x->value];
	while(adjNode)
	{
	    relax(x->value, adjNode->vertex, adjNode->weight ,d, parent);
	    adjNode = adjNode->next;
	}
	x = x->next;
    }
    free_list(list);
}







