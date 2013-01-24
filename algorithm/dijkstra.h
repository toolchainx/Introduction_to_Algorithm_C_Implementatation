#ifndef _DIJKSTRA_H_
#define _DIJKSTRA_H_


// 实现dijkstra算法
// 优先级队列的实现对照prim算法
// 优先级队列排序的关键字为顶点的d值，即最短路径估计值
// 因此就要将d作为Fibonacci堆中结点的某一成员吗？ 如何处理这一扩展问题？
// 看看prim算法的排序的关键字
// 算法的相似性对照prim算法和广度搜索算法
// 利用Fibonacci堆实现
// 关键在于解决优先级队列和图的相互引用的问题
#include "include/require.h"
#include "adj_table.h"
#include "fib_heap.h"
#include "single_source_shortest_path.h"

// 根据图生成优先队列
// graph为图
// gSize为顶点的个数
// key为数组，保存初始化的权重
// h为Fibonacci heap
// fpnArray为保存优先队列中每个结点指针的数组
void construct_queue(AdjList graph[], int gSize, int key[], FibHeap h, FibHeapNodePtr fpnArray[]);
void dijkstra_relax(int u, int v, int w, int parent[], FibHeapNodePtr fpnArray[], FibHeap h);
// 将d[]拷贝到优先队列中，在优先队列中对d进行修改(decreace_key)
// 处理完成后，再拷贝出来
// 假定graph，d[]，parent[]均已分配内存
void dijkstra(AdjList* graph, int numVertices, int s, int d[], int parent[]);


#endif /* _DIJKSTRA_H_ */
