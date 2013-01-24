#include <stdio.h>
#include <math.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "adj_table.h"



void adj_set_weight(AdjListNodePtr adjpnode, int weight)
{
    adjpnode->weight = weight;
}

// 一个链表中插入一个元素
// 直接在链表前端插入？

AdjList adj_insert(AdjList adjl, int value)
{
    // 根据在哪里分配就在哪里释放的原理，在这里分配内存合适吗？
    // 为新结点分配内存
    AdjListNodePtr new = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    if (!new)
    {
	printf("malloc failed\n");
	exit(EXIT_FAILURE);
    }
    
    new->vertex = value;
    new->weight = 0;
    new->next = NULL;
    // next 指向要插入位置的下一个元素
    if (adjl)
    {
	// error here!!!
	new->next = adjl->next;
	adjl->next = new;
    }
    else
    {
	adjl = new;
    }
    return adjl;
    
}
// 创建并插入一个带有权重的结点
// adj_list是一个链表，不是一个结点，待续...
AdjList adj_weight_insert(AdjList adjl, int value, int weight)
{
    // 根据在哪里分配就在哪里释放的原理，在这里分配内存合适吗？
    // 为新结点分配内存
    AdjListNodePtr new = (AdjListNodePtr)malloc(sizeof(AdjListNode));
    if (!new)
    {
	printf("malloc failed\n");
	exit(EXIT_FAILURE);
    }
    
    new->vertex = value;
    new->weight = weight;
    new->next = NULL;
    // next 指向要插入位置的下一个元素
    if (adjl)
    {
	// error here!!!
	new->next = adjl;
	adjl = new;
    }
    else
    {
	adjl = new;
    }
    return adjl;
}

// 释放链表
void freeList(AdjList adjl)
{
    AdjList current = adjl;
    while (adjl) {
	current = current->next;
	free(adjl);
	adjl = current;
    }
}
// 释放邻接链表
void free_adjlist(AdjList adjl[], int count)
{
    int i;
    for (i = 0; i < count; i++) {
	freeList(adjl[i]);
    }
    free(adjl);
}
// 增加数组的长度
AdjList* arr_realloc(AdjList* adjList, int* parrLength)
{
    size_t newsize, oldsize = *parrLength * sizeof(AdjList);
    adjList = (AdjList *)realloc(adjList, oldsize + INCREMENT_SIZE*sizeof(AdjList));
    *parrLength += INCREMENT_SIZE;
    newsize = *parrLength * sizeof(AdjList);
    if (!adjList)
    {
	printf("realloc failed\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // 在使用变量时，要时刻记住变量的类型
    memset(adjList+(oldsize/sizeof(AdjList)), 0, newsize - oldsize);
    return adjList;
}
// 输出邻接链表
void print_adjlist(AdjList adjList[], int length)
{
    int i =0;
    printf("%d\n" ,length);
    for (i = 0; i < length; ++i)
    {
	AdjListNodePtr current = adjList[i];
	while(current != NULL)
	{
	    printf("%d -> %d, ", i, current->vertex);
	    printf("weight: %d; ", current->weight);
	    fflush(stdout);
	    current = current->next;
	}
	printf ("\n");
    }
    printf("\n");
}

AdjList* construct_weighted_adjlist(const char* filename, AdjList*
                                      adjList, int* pnumVertices)
{
    int inode;
    int icount = 0;
    int count;
    int arrLength = ALLOC_SIZE;
    FILE *pFile;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open %s\n", filename);
	fflush(stdout);
	fclose(pFile);
	exit(EXIT_FAILURE);
    }
    // 如何动态扩充数组的大小？
    // the memory is set to zero.
    adjList = (AdjList*)calloc(ALLOC_SIZE,  sizeof(AdjList));
    if (adjList == NULL)
    {
	printf("can't calloc for adjList\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    do
    {
	int tmpvalue;
	int i = 0;
	fscanf(pFile, "%d", &inode);
	// 动态增加数组的长度
	if (inode >= ALLOC_SIZE)
	{
	    adjList = arr_realloc(adjList, &arrLength);
	}
	icount++;
	fscanf(pFile, "%d", &count);
	if (count == 0)
	{
	    adjList[inode] = NULL;
	    continue;
	}
	do
	{
	    int tmpweight;
	    fscanf(pFile, "%d %d", &tmpvalue, &tmpweight);
	    // 构建第 inode个结点的邻接链表
	    adjList[inode] = adj_weight_insert(adjList[inode], tmpvalue, tmpweight);
	    printf("adjnode value: %d weight: %d\n", adjList[inode]->vertex, adjList[inode]->weight);
	    i++;
	} while (i < count);
    } while (!feof(pFile));
    printf("input ended\n");
    fflush(stdout);
    print_adjlist(adjList, icount);
    fclose(pFile);
    *pnumVertices = icount;
    return adjList;
    
}
AdjList* construct_adjlist(const char* filename, AdjList* adjList,
                             int* pnumVertices)
{
     // 如何动态扩充数组的大小？
    // the memory is set to zero.
    adjList = (AdjList*)calloc(ALLOC_SIZE, sizeof(AdjList));
    // adj_list adjList[10] = {NULL};
    int inode;
    int icount = 0;
    int count;
    int arrLength = ALLOC_SIZE;
    FILE *pFile;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open %s\n", filename);
	fflush(stdout);
	fclose(pFile);
	exit(EXIT_FAILURE);
    }
    do
    {
	int tmpvalue;
	int i;
	//printf ("input the node\n");
	fscanf(pFile, "%d", &inode);
	// 动态增加数组的长度
	if (inode >= ALLOC_SIZE)
	{
	    adjList = arr_realloc(adjList, &arrLength);
	}
	icount++;
	fscanf(pFile, "%d", &count);
	if (count == 0)
	{
	    continue;
	}
	i = 0;
	do
	{
	    fscanf(pFile, "%d", &tmpvalue);
	    // 构建第 inode个结点的邻接链表
	    adjList[inode] = adj_insert(adjList[inode], tmpvalue);
	    i++;
	} while (i < count);
    } while (!feof(pFile));
    printf("input ended\n");
    fflush(stdout);
    print_adjlist(adjList, icount);
    fclose(pFile);
    *pnumVertices = icount;
    return adjList;
}
AdjList* copy_adjlist(AdjList* graph, int numVertices)
{
    int i;
    AdjList* gQuote;
    gQuote = (AdjList*)calloc(numVertices, sizeof(AdjList));
    for (i = 0; i < numVertices; i++) {
	AdjListNodePtr x = graph[i];
	while (x) {
	    gQuote[i] = adj_weight_insert(gQuote[i], x->vertex, x->weight);
	    x = x->next;
	}
    }
    // remember to free the gQuote outside the function.
    return gQuote;
}
// 判断一条边是否存在
EBool edge_exist(AdjList* graph, int numVertices, int u, int v)
{
    AdjListNodePtr x = graph[u];
    while(x)
    {
	if (x->vertex == v)
	{
	    return TRUE;
	}
	x = x->next;
    }
    return FALSE;
}

// 要更新一个残留网络，首先图要支持的功能是，增加一条边和减少一条边
// 假设顶点均存在
EBool add_edge(AdjList* graph, int numVertices, int u, int v)
{
    if (edge_exist(graph, numVertices, u, v))
    {
	return FALSE;
    }
    graph[u] = adj_insert(graph[u], v);    
    return TRUE;
}
// 假设顶点均存在
EBool del_edge(AdjList* graph, int numVertices, int u, int v)
{
    // 要删除一个结点，我得记住该结点的前一个结点
    AdjListNodePtr pre_x=NULL, x;
    if (!edge_exist(graph, numVertices, u, v))
    {
	return FALSE;
    }
    x = graph[u];
    while (x) {
	if (x->vertex == v)
	{
	    // 分两种情况，x指向第一个结点，或者x没有指向第一个结点
	    if (x == graph[u])
	    {
		graph[u] = x->next;
		free(x);
	    }
	    else
	    {
		assert(pre_x != NULL);
		pre_x->next = x->next;
		free(x);
	    }
	}
	pre_x = x;
	x = x->next;
    }
    return TRUE;
}

/* int main(int argc, char *argv[]) */
/* { */
/*     adj_list* pAdjl = NULL; */
/*     int numVertices; */
/*     if (argc != 2) */
/*     { */
/* 	printf("input the data file\n"); */
/* 	exit(EXIT_FAILURE); */
/*     } */
/*     pAdjl =  construct_adj_list(argv[1], pAdjl, &numVertices); */
/*     freeAdjList(pAdjl, numVertices); */
/*     return 0; */
/* } */
