// prim 算法
// 思路：
// key[u] parent[u] 用数组实现，元素的个数为顶点的个数
// 如何将邻接链表或者邻接矩阵表示的图放入优先队列中？
// insert_node()
// 如何判断一个元素是否在优先队列中？
// 为每个顶点留出一位的空间来记录该结点是否在队列Q中，在顶点移除队列时，对该位进行更新
// 利用key域确定优先级的大小
// 利用inq域(type is Mark)来确定是否在优先级队列中
// 图和最小优先队列需要相互引用
// 最小优先队列的结点用什么来索引？ 数组

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "fib_heap.h"
#include "adj_table.h"

#define NOP -1

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
// 打印最小生成树
// 最小生成树满足
// A = {(v, parent(v) : v is a member of V - {idx})}
void mst_prim_print(int parent[], int size, int idx)
{
    int i;
    for (i = 0; i < size; i++) {
	if (parent[i] != NOP)
	{
	    printf("edge: %d -> %d\n", i, parent[i]);
	}
    }
    printf("\n");
}
// adj_list是指向结点的指针
// graph 是数组，数组的元素为adj_list指针
// gSize 为数组元素的个数
// r为数组的索引
// u, v为指针
// 利用元素为指针的数组来索引优先级队列中的所有元素
void mst_prim(adj_list* graph, int gSize, int rIdx)
{
    int i;
    int key[gSize];
    adj_pnode v;
    int parent[gSize];
    FibHeap h = make_fib_heap();
    FbhPNode fpnArray[gSize];
    for (i = 0; i < gSize; i++) {
	key[i] = INT_MAX;
	parent[i] = NOP;
    }
    key[rIdx] = 0;
    // 将图中所有的顶点放入优先级队列中
    construct_queue(graph, gSize, key, h, fpnArray);
    fib_heap_root_print(h->min);
    while (h->min != NIL) {
	FbhPNode u = fib_heap_extract_min(h);
	printf("extract_min: %d\n", u->ref);
	/* printf("after extract_min\n"); */
	/* fib_heap_root_print(h->min); */
	u->inq = FALSE;
	// u->ref 指向图顶点的索引
	// v 指向邻接链表的某一结点
	// 用于迭代
	v = graph[u->ref];
	while (v) {
	    if (fpnArray[v->vertex]->inq == TRUE
		&& v->weight < fpnArray[v->vertex]->key)
	    {
		parent[v->vertex] = u->ref;
		fib_heap_decrease_key(h, fpnArray[v->vertex], v->weight);
	    }
	    v = v->next;
	}
    }
    mst_prim_print(parent, gSize, rIdx);
}



int main(int argc, char *argv[])
{
    adj_list* graph =  NULL;
    int numVertices;
    // 构建邻接链表，将数据从mst_prim.dat文件中读入
    int rIdx;
    printf("input the rIdx\n");
    fflush(stdout);
    scanf("%d", &rIdx);
    graph = construct_weighted_adj_list(argv[1], graph, &numVertices);
    mst_prim(graph, numVertices, rIdx);
    return 0;
}
