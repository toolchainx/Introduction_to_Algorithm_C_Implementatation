// 实现单源最短路径算法的公共部分
// 图用邻接链表实现
// 最小优先队列用Fibonacci堆实现
// 主要实现的函数有两个
// 初始化函数
// 松弛函数
// 如何存放每个顶点的最短路径估计d[v]
// 当利用优先队列进行排序式，其关键字为最短路径估计
// 如何存放每个顶点的前驱parent[v]
// 解决方案一，利用动态的数组

#include "single_source_shortest_path.h"


// 假定动态数组d[],parent[]已分配好
// 假定邻接链表已分配好，长度给定
// 根据DRY原则，是否要去掉length参数
// 通过遍历graph来获得graph的长度呢？
void initialize_single_source(AdjList* graph, int length, int s, 
			      int d[], int parent[])
{
    int i;
    for (i = 0; i < length; i++) {
	d[i] = INT_MAX;
	parent[i] = NILVALUE;
    }
    d[s] = 0;
}

// 实现松弛函数
// 对v进行松弛，w是u->v的边的权值
void relax(int u, int v, int w, int d[], int parent[])
{
    if (d[v] > d[u] + w)
    {
	d[v] = d[u] + w;
	parent[v] = u;
    }
}

// Bellman-Ford 算法

// 假定graph, d[], parent[]均已分配好
EBool bellman_ford(AdjList* graph, int length, int s, int d[], int parent[])
{
    int i, m;
    initialize_single_source(graph, length, s, d, parent);
    for (i = 0; i < length - 1; i++) {
	// 遍历每条边，对每条边进行松弛
	int j;
	for (j = 0; j < length; j++) {
	    AdjListNodePtr x = graph[j];
	    while (x) {
		relax(j, x->vertex, x->weight, d, parent);
		x = x->next;
	    }
	}
    }
    // 测试是否有负权回路
    for (m = 0; m < length; m++) {
	AdjListNodePtr x = graph[m];
	while(x) {
	    if (d[x->vertex] > d[m] + x->weight)
	    {
		return FALSE;
	    }
	    x = x->next;
	}
    }
    return TRUE;    
}
