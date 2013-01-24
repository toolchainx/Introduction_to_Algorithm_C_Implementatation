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

#include <stdio.h>
#include <stdlib.h>
#include "include/require.h"
#include "adj_table.h"
#include "print_path.h"


// 假定动态数组d[],parent[]已分配好
// 假定邻接链表已分配好，长度给定
// 根据DRY原则，是否要去掉length参数
// 通过遍历graph来获得graph的长度呢？
void initialize_single_source(AdjList* graph, int length, int s, 
			      int d[], int parent[]);

// 实现松弛函数
// 对v进行松弛，w是u->v的边的权值
void relax(int u, int v, int w, int d[], int parent[]);

// Bellman-Ford 算法

// 假定graph, d[], parent[]均已分配好
EBool bellman_ford(AdjList* graph, int length, int s, int d[], int parent[]);

