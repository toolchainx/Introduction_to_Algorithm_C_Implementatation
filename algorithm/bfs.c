// 实现邻接链表的广度优先搜索
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include "include/require.h"
#include "queue.h"
#include "stack.h"
#include "adj_table.h"
#include "bfs.h"

// 广度优先搜索的本质的遍历图，并进行操作
// 操作主要目的是对邻接链表的parent成员以及distance成员进行赋值
// 在赋值的过程中，邻接链表的color成员进行辅助
// 同时进行辅助作用的是一个FIFO queue
// 考虑以上因素对bfs的函数接口进行设计
// 前提假定distance和parent均已分配好
adj_list* bfs(adj_list* pAdjl, int numVertices, int org_vertex, int* distance, int* parent)
{
    // for breadth-first search
    Color *color = (Color*)malloc(numVertices * sizeof(Color));
    int i;
    queue q;
    // 根据顶点初始化队列操作
// 初始化队列为空
    q.head = q.tail = 0;

// 初始化操作
// 该处有个设计问题，每个顶点的颜色，父亲，距离，应该放置在何处？
// 第一种设计方法：重新设计邻接链表的结构，使得数组中的元素指
// 向一个结构体，该结构体
// 包含两部分：一部分指向链表
// 另一部分为该顶点的卫星数据
// 当边含有权值时，在链表中添加成员weight
// 考虑设计的合理性
    
// 第二种设计方法：保持原有的邻接链表的简单数据结构不变(只包含顶点索引，
// 以及next指针，或许再加上权值)。
// 分配3个数组:每个数组的下标为顶点的索引
// color[]:保存每个顶点的颜色
// distance[]:保存每个顶点的距离
// parent[]:保存每个顶点的父结点
// 思考，两种设计的思路体现了怎样的设计哲学？
// 目前采用第二种策略
    for (i = 0; i < numVertices; i++) {
	if (i != org_vertex)
	{
	    color[i] = WHITE;
	    distance[i] = INFINITE;
	    parent[i] = NILVALUE;	    
	}
    }
    color[org_vertex] = GRAY;
    distance[org_vertex] = 0;
    parent[org_vertex] = NILVALUE;
// 将元素org_vertex入队
    enqueue(&q, org_vertex);
// 开始搜索
    while (q.head != q.tail) {
	int u;
	adj_list pv;
	dequeue(&q, &u);
	pv = pAdjl[u];
	while (pv) {
	    if (color[pv->vertex] != WHITE)
	    {
		pv = pv->next;
		continue;
	    }
	    color[pv->vertex] = GRAY;
	    distance[pv->vertex] = distance[u] + 1;
	    parent[pv->vertex] = u;
	    enqueue(&q, pv->vertex);
	    pv = pv->next;
	}
// 将出队的顶点都置为黑色
	color[u] = BLACK;
    }
    free(color);
    return pAdjl;
}
static void print(int point)
{
    printf("%d ", point);
}
// 打印两点间的最短路径所经过的中间点
// 计算两个顶点间的最短路径，将路径中经过的顶点索引按s->t顺序保存在数组中
// path数组的内存已分配好
EBool calc_path(adj_list* graph, int numVertices, int* parent, int s, int t, Stack path)
{
    int x = t;
    while (x != s) {
	if (parent[x] == NILVALUE)
	{
	    return FALSE;
	}
	push(path, x);
	x = parent[x];
    }
    push(path, s);
    return TRUE;
}
// 如何将该函数的递归版本改成迭代版本？ 递归版本需要传递的参数的数量太多
void print_path(adj_list* pAdjl, int numVertices, int* parent, int start, int end)
{
    if (start == end)
    {
	print(start);
    }
    else if (parent[end] == NILVALUE)
    {
	printf("no path from %d to %d exist\n", start, end);
    }
    else
    {
	print_path(pAdjl, numVertices, parent, start, parent[end]);
	print(end);
    }
}

EBool peek(Stack s, int idx, int *pv)
{
    int i;
    List x = s->next;
    for (i = 0; i < idx && x != NULL; i++) {
	x = x->next;
    }
    if (x == NULL)
    {
	return FALSE;
    }
    *pv = x->value;
    return TRUE;
}










