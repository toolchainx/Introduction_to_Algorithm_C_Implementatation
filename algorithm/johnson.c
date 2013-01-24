// 稀疏图上的johnson算法
// 采用了重赋权技术
// 采用邻接链表实现图的结构
// 利用了Dijkstra算法和Bellman-Ford算法作为其子程序
#include "johnson.h"

// 源点到其他各顶点的距离为0
// 返回source顶点的索引
AdjList* add_source_vertex(AdjList* graph, int numVertices, int* sIdx)
{
    int i;
    AdjList* gQuote = copy_adjlist(graph, numVertices);
    print_adjlist(gQuote, numVertices);
    // realloc分配的内存，一定要记住清零
    gQuote = (AdjList *)realloc(gQuote, (numVertices + 1)* sizeof(AdjList));
    gQuote[numVertices] = NULL;
    if (gQuote == NULL)
    {
	printf("can't realloc for gQuote\n");
	exit(EXIT_FAILURE);
    }
    for (i = 0; i < numVertices; i++) {
	adj_weight_insert(gQuote[numVertices], i, 0);
    }
    *sIdx = numVertices;
    return gQuote;    
}

AdjMat* johnson(AdjList* graph, int numVertices)
{
    int u, v;
    AdjList* gQuote;
    int sIdx;
    int *h, *parent, *dQuote, *parentQuote;
    AdjMat* dMat = make_adjmat(numVertices);
    h = (int *)malloc((numVertices + 1) * sizeof(int));
    parent = (int *)malloc((numVertices + 1) * sizeof(int));
    dQuote = (int *)malloc((numVertices + 1) * sizeof(int));
    parentQuote = (int *)malloc((numVertices + 1) * sizeof(int));
    gQuote =  add_source_vertex(graph, numVertices, &sIdx);
    print_adjlist(gQuote, numVertices + 1);
#ifdef DEBUG
    printf("johnson started\n");
    fflush(stdout);
#endif // DEBUG    

    if (bellman_ford(gQuote, numVertices+1, sIdx, h, parent) == FALSE)
    {
	printf("the input graph contains a negtive-weight cycle\n");
	return NULL;
    }
    else
    {
	// 设计一个遍历函数和一个对每个遍历的结点进行修改的函数？
	int i;
	for (i = 0; i < numVertices+1; i++) {
	    AdjListNodePtr x = gQuote[i];
	    while (x) {
		x->weight = x->weight + h[i] - h[x->vertex];
		x = x->next;
	    }
	}
    }
    for (u = 0; u < numVertices; u++) {
	// 将u作为源点利用Dijkstra算法计算最短路径
	// need to zero the dQuote and parentQuote?
	dijkstra(gQuote, numVertices+1, u, dQuote, parentQuote);
	for (v = 0; v < numVertices; v++) {
	    dMat->mat[u][v] = dQuote[v] + h[v] - h[u];
	}
    }
    free(h);
    free(parent);
    free(dQuote);
    free(parentQuote);
    free_adjlist(gQuote, numVertices + 1);
    // remember to free the dMat outside the function.
#ifdef DEBUG
    printf("johnson finished\n");
    fflush(stdout);    
#endif // DEBUG    
    return dMat;
}
