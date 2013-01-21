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
void construct_queue(adj_list graph[], int gSize, int key[], FibHeap h, FbhPNode fpnArray[])
{
    FbhPNode x;
    int i;
    for (i = 0; i < gSize; i++) {
	x = fib_heap_node_allocate(i);
	x->key = key[i];
	x->ref = i;
	fpnArray[i] = x;
	fib_heap_insert(h, x);
    }
}

void dijkstra_relax(int u, int v, int w, int parent[], FbhPNode fpnArray[], FibHeap h)
{
    if (fpnArray[v]->key > fpnArray[u]->key + w)
    {
	fib_heap_decrease_key(h, fpnArray[v], fpnArray[u]->key +w);
	parent[v] = u;
    }
}
// 将d[]拷贝到优先队列中，在优先队列中对d进行修改(decreace_key)
// 处理完成后，再拷贝出来
// 假定graph，d[]，parent[]均已分配内存
void dijkstra(adj_list* graph, int numVertices, int s, int d[], int parent[])
{
    int i;
    adj_pnode v;
    FibHeap h = make_fib_heap();
    FbhPNode fpnArray[numVertices];
    initialize_single_source(graph, numVertices, s, d, parent);
    construct_queue(graph, numVertices, d, h, fpnArray);
    fib_heap_root_print(h->min);
    while(h->min !=  NIL)
    {
	FbhPNode u = fib_heap_extract_min(h);
	printf("extract_min: %d\n", u->ref);
	// 指示顶点u已不再优先队列中
	u->inq = FALSE;
	v = graph[u->ref];
	// 对以u->ref为顶点的每条边进行松弛
	while(v)
	{
	    // 有无代码依赖于parent[]的修改？
	    // 循环的下一次迭代依赖于优先队列中关键字域的修改
	    dijkstra_relax(u->ref, v->vertex, v->weight, parent, fpnArray, h);
	    v = v->next;
	}
	
    }
    // 将队列中关键字的值拷贝回d中，利用fpnArray[]
    for (i = 0; i < numVertices; i++) {
	d[i] = fpnArray[i]->key;
    }
    // 释放优先队列中的内存...
}
