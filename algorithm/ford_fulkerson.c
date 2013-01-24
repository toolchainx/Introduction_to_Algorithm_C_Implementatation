// 实现最大流的ford_fulkerson方法
// 具体实现采用Edmonds_Karp算法
// 图采用邻接链表实现
// 查找源点到汇点的路径使用bfs算法
// 每对顶点的最大流使用邻接矩阵表示
// 每对顶点的残留容量使用邻接矩阵表示
// 最短路径上的各顶点用path[]数组表示
#include "ford_fulkerson.h"

// 假定graph和flow已分配内存
// graph已初始化
void initialize_edge_flow(AdjList* graph, int numVertices, AdjMat* flow)
{
    int i;
    for (i = 0; i < numVertices; i++) {
	AdjListNodePtr x = graph[i];
	while (x) {
	    flow->mat[i][x->vertex] = 0;
	    flow->mat[x->vertex][i] = 0;
	    x = x->next;
	}
    }
}
// 该处path用栈来表示？
// 使用make_stack来创建Stack
EBool find_shortest_path(AdjList* graph, int numVertices, int s, int t, Stack path)
{
    int *distance = (int *)malloc(numVertices * sizeof(int));
    int *parent = (int *)malloc(numVertices * sizeof(int));
    bfs(graph, numVertices, s, distance, parent);
#ifdef DEBUG
    print_path(graph, numVertices, parent, s, t);
#endif // DEBUG
    return calc_path(graph, numVertices, parent, s, t, path);
}


int rc(int u, int v, AdjMat* f, AdjMat* c)
{
    int rCap = c->mat[u][v] - f->mat[u][v];
    return rCap;
}

int min_res_cap(AdjMat* c, AdjMat*f, Stack path)
{
    int i=0, u, v, min = INFINITE;
    if(peek(path, i++, &u))
    {
	while (peek(path, i++, &v)) {
	    int uv = rc(u, v, f, c);
	    assert(uv > 0);
	    assert(u != v);
	    min = uv < min? uv:min;
	    u = v;
	}	
    }
    return min;
}
void update_flow(AdjMat* f, Stack path, int cfp)
{
    int i = 0, u,v;
    if (peek(path, i++, &u))
    {
	while (peek(path, i++, &v)) {
	    assert(u != v);
	    f->mat[u][v] = f->mat[u][v] + cfp;
	    f->mat[v][u] = -f->mat[u][v];
	    u = v;
	}
    }
}

// 更新残留网络
void update_residual_graph(AdjList* gQuote, int numVertices, AdjMat* c, AdjMat* f, Stack path)
{
    // 如何更新？
    // 要更新一个残留网络，首先图要支持的功能是，增加一条边和减少一条边
    // 残留网络需要更新的部分只是在最短路径上
    int u, v;
    if (pop(path,&u))
    {
	while (pop(path, &v)) {
	    assert(u !=  v);
	    if (rc(u, v, f, c) > 0)
	    {
		add_edge(gQuote, numVertices, u, v);
	    }
	    else if (rc(u,v,f,c) == 0)
	    {
		assert(del_edge(gQuote, numVertices, u, v) == TRUE);
	    }
	    if (rc(v, u, f, c) > 0)
	    {
		add_edge(gQuote, numVertices, v, u);
	    }
	    else if (rc(v, u, f, c) == 0)
	    {
		assert(del_edge(gQuote, numVertices, v, u) == TRUE);
	    }
	    u = v;
	}
    }
}
// 输入
// 输出
// 函数的功能
// 副作用
// 假定graph, f和c已分配内存
// graph和c已初始化完成
// 问题：何时更新残留容量，直接计算，不存储?
// c 表示的是图初始化时的容量，不是残留容量
void ford_fulkerson(AdjList* gQuote, int numVertices, int s, int t, AdjMat* f, AdjMat* c)
{
    Stack path = make_stack();
    int minResCap;
    //adj_list* gQuote = copy_adjlist(graph, numVertices);
    print_adjlist(gQuote, numVertices);
    initialize_edge_flow(gQuote, numVertices, f);
    print_adjmat(f);
    // 循环无法终止
    while (find_shortest_path(gQuote, numVertices, s, t, path)) {
	// 如何查看栈中的所有元素而又不删除这个元素？
	printf("shortest path found\n");
	print_stack(path);
	printf("\n");
	fflush(stdout);
	minResCap = min_res_cap(c, f,  path);
#ifdef DEBUG
	printf("minResCap = %d\n", minResCap);
#endif // DEBUG
	update_flow(f, path, minResCap);
	printf("updated_flow\n");
	print_adjmat(c);
	print_adjmat(f);
	// 问题：如何从G生成Gf
	update_residual_graph(gQuote, numVertices, c, f, path);
	print_adjlist(gQuote, numVertices);
	fflush(stdout);
    }
    //freeAdjList(gQuote, numVertices);
}












