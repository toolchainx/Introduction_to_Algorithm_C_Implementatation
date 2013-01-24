// 图深度优先搜索算法实现
// 如何去掉全局变量
// 取消可使用的参数个数的限制
// 深度优先搜索的两大应用
// 进行拓扑排序
// 把一个有向图分解为各强连通分支
// 根据应用来决定其输出
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include "dfs.h"


// 根据结束时间f来对图进行拓扑排序
// 深度优先搜索，函数接口的设计
// 输入参数：邻接链表adj_list*,邻接链表中顶点的个数，
// 输出参数：邻接链表adj_list*, 
// 改变的值：d[],f[],color[](起辅助作用),parent[], 
// 改变的值：list(save the result of the toplogical_sort() function);
EBool dfs_visit(int i, AdjList* graph, int numVertices, EColor * color, int* parent, int* d, int* f);
// 假定graph parent, d, f的内存已分配好
EBool dfs(AdjList* graph, int numVertices, int *parent, int* d, int* f, int *seq)
{
    int i;
    // 对数据结构进行初始化操作
    EColor *color = (EColor *)malloc(numVertices * sizeof(EColor));
    for (i = 0; i < numVertices; i++) {
	color[i] = WHITE;
	parent[i] = NILVALUE;
	d[i] = 0;
	f[i] = 0;
    }
    // 注意边界条件，初始化操作和结束操作
    for (i = 0; i < numVertices; i++) {
	int n = (seq == NULL)? i:seq[i];
	if (color[n] == WHITE)
	{
	    // 多次调用dfs_visit
	    dfs_visit(n, graph, numVertices, color, parent, d, f);
	}
	printf("---------------------\n");
    }
    return TRUE;
}

void set_edge_type(int start, AdjList pendnode, EColor *color, int* d);
// 该过程是个递归调用的过程
EBool dfs_visit(int i, AdjList* graph, int numVertices, EColor* color, int* parent, int* d, int* f)
{
    // 静态变量Time，在多次调用间，保持storage duration
    static int Time = 0;
    // 确定i在有效范围内
    AdjList pnode = graph[i];
    assert(i >= 0);
    color[i] = GRAY;
    d[i] = ++Time;
    printf("d[%d] = %d\n", i, d[i]);
    while (pnode) {
	set_edge_type(i, pnode, color, d);
	if (color[pnode->vertex] == WHITE)
	{
	    // pnode->edgeType = TREE;
	    // printf("the edge type of %d to %d is %d");
	    // print_edgetype(i, pnode->vertex, pnode->edgeType);
	    parent[pnode->vertex] = i;
	    printf("parent[%d] = %d\n", pnode->vertex, 
		   parent[pnode->vertex]);
	    dfs_visit(pnode->vertex, graph, numVertices, color, parent, d, f);
	}
	pnode = pnode->next;
    }
    color[i] = BLACK;
    f[i] = ++Time;  
    printf("f[%d] = %d\n", i, f[i]);
    return TRUE;
}

void print_edgetype(int start, int end, int type)
{
    char typename[10];
    switch(type){
    case TREE:
	strcpy(typename, "tree edge");
	break;
    case BACK:
	strcpy(typename, "back edge");
	break;
    case FORWARD:
	strcpy(typename, "forward edge");
	break;
    case CROSS:
	strcpy(typename, "cross edge");
	break;
    default:
	printf("wrong edge type\n");
	return;
    }
    printf("%d -> %d %s\n", start, end, typename);
}
void set_edge_type(int start, AdjList pendnode, EColor *color, int *d)
{
    switch(color[pendnode->vertex])
    {
    case WHITE:
	pendnode->edgeType = TREE;
	break;
    case GRAY:
	pendnode->edgeType = BACK;
	break;
    case BLACK:
	if (d[start] < d[pendnode->vertex])
	{
	    pendnode->edgeType = FORWARD;
	}
	else
	{
	    pendnode->edgeType = CROSS;	    
	}
	break;
    default:
	printf("wrong color type\n");
    }
    print_edgetype(start, pendnode->vertex, pendnode->edgeType);
}
// output the value in every element of the array
void print_array(const char* arr_name, int arr[], int length)
{
    int i;
    for (i = 0; i < length; i++) {
	printf("%s[%d] = %d\n",arr_name, i, arr[i]);
    }
}
