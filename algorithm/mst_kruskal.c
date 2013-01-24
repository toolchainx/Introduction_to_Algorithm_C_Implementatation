// Kruskal 算法
// 关键问题：如何将图的邻接链表表示和不相交集合数据结构结合起来
// 在Kruskal 算法的实际实现中图和不相交数据集合的表示是需要互相引用的
// 亦即，表示一个顶点的对象会包含一个指向对应不相交集合对象的指针，反之亦然。
// 这些编程细节与具体的实现语言有关。
// 不相交集合的链表只需要来表示顶点，不用表示边，边由邻接链表来表示
// 问题1
// 利用邻接链表，如何对集合的边进行排序？
// 解决方案1，每个链表的结点包含该边的起点指针
// 解决方案2，用一个数组重新保存边的起点和终点
// 问题2
// 如何区别有向边和无向边
// 解决办法：在边输入的时候不给出双向的边
// 输出：哪些边构成了最小生成树
// 或者利用管道的思想：输入的是图，输出也是图


#define INFINITE 0
#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "disjoint_set_forest.h"

// 定义边的类型
typedef struct tagEdge
{
    int startPointIndex;
    int endPointIndex;
}EEdge;

// 图的表示方法，利用邻接矩阵来表示图，也就是二维数组
#define NUMVERTICES 9

int calcEdge(int g[NUMVERTICES][NUMVERTICES], int cntVertices,  EEdge* edge)
{
    int i, j, edgeNum = 0;
    // 避免一条边的两个方向都计算
    for (i = 0; i < cntVertices; i++) {
	for(j = 0; j < i; j++)
	{
	    if (g[i][j] != INFINITE)
	    {
		if(edge != NULL)
		{
		    edge[edgeNum].startPointIndex = i;
		    edge[edgeNum].endPointIndex = j;
		}
		edgeNum++;
	    }
	}
    }
    return edgeNum;
}

void edge_print(EEdge* edge, int cntEdges)
{
    int i;
    for (i = 0; i < cntEdges; i++) {
	printf("%d -> %d\n",edge[i].startPointIndex, 
	                    edge[i].endPointIndex);
    }
    printf("\n");

}


void swapEdge(EEdge* edge, int i, int j)
{
    EEdge tmp;
    tmp.startPointIndex = edge[i].startPointIndex;
    tmp.endPointIndex = edge[i].endPointIndex;
    edge[i].startPointIndex = edge[j].startPointIndex;
    edge[i].endPointIndex = edge[j].endPointIndex;
    edge[j].startPointIndex = tmp.startPointIndex;
    edge[j].endPointIndex = tmp.endPointIndex;
}
// 对所有的边，按权重进行排序，根据给定的函数进行排序
void sortEdge(EEdge edge[], int cntEdges, int g[NUMVERTICES][NUMVERTICES])
{
    // 简单选择排序
    int i, j;
    for (i = 0; i < cntEdges - 1; i++) {
	for(j = i; j < cntEdges; j++)
	{
	    if (g[edge[i].startPointIndex][edge[i].endPointIndex] 
		> g[edge[j].startPointIndex][edge[j].endPointIndex])
	    {
		// 交换两条边
		swapEdge(edge, i, j);
	    }
	}
    }

}
// 直接输出最小生成树的边
void mst_kruskal(int g[NUMVERTICES][NUMVERTICES], int cntVertices)
{
    int i;
    int cntEdges, newCntEdges;
    EEdge *edge;
    // 如何分配内存？
    // 计算要分配的数量，然后再分配，还是一个一个的分配？
    cntEdges = calcEdge(g, cntVertices, NULL);
    edge = (EEdge*)malloc(cntEdges * sizeof(EEdge));
    newCntEdges = calcEdge(g, cntVertices, edge);
    printf("before sort\n");
    edge_print(edge, cntEdges);
    assert(newCntEdges == cntEdges);
    // 保存结点指针的数组
    DjsTreeNodePtr nodeArray[NUMVERTICES];
    for (i = 0; i < cntVertices; i++) {
	nodeArray[i] = djsforest_make_node(i);
	djsforest_make_set(nodeArray[i]);
    }
    // 对所有的边，按权重进行排序，根据给定的函数进行排序
    sortEdge(edge, cntEdges, g);
    printf("after sort\n");
    edge_print(edge, cntEdges);
    for (i = 0; i < cntEdges; i++) {
	// edge按权重从小到大排序之后
	if (djsforest_find_set(nodeArray[edge[i].startPointIndex]) 
	    != djsforest_find_set(nodeArray[edge[i].endPointIndex]))
	{
	    printf("edge: %d -> %d\n", edge[i].startPointIndex, edge[i].endPointIndex);
	    djsforest_union(nodeArray[edge[i].startPointIndex], nodeArray[edge[i].endPointIndex]);
	}
    }
    // free the nodeArray
    for (i = 0; i < NUMVERTICES; i++) {
	free(nodeArray[i]);
    }

}
void adj_matrix_read(int g[NUMVERTICES][NUMVERTICES], int cntVertices, int start, int end, int weight)
{
    if (start >= cntVertices && end >= cntVertices)
    {
	printf("index exceed the scope: %d -> %d", start, end);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    g[start][end] = weight;
    g[end][start] = weight;
}
void adj_matrix_print(int g[NUMVERTICES][NUMVERTICES], int cntVertices)
{
    int i, j;
    // 避免一条边的两个方向都计算
    for (i = 0; i < cntVertices; i++) {
	for(j = 0; j < i; j++)
	{
	    if (g[i][j] != INFINITE)
	    {
		printf("%d -> %d : %2d\t", i, j, g[i][j]);
	    }
	}
	printf("\n");
    }
}


int main(int argc, char *argv[])
{
    // 构建邻接矩阵图
    int graph[NUMVERTICES][NUMVERTICES];
    FILE* pf;
    memset(graph, 0, sizeof(int)*NUMVERTICES * NUMVERTICES);
    if ((pf = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open file %s\n", argv[1]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    while(!feof(pf))
    {
	int start, end, weight;
	fscanf(pf, "%d %d %d", &start, &end, &weight);
	adj_matrix_read(graph, NUMVERTICES, start, end, weight);
    }
    adj_matrix_print(graph, NUMVERTICES);
    fclose(pf);
    mst_kruskal(graph, NUMVERTICES);
    return 0;
}
