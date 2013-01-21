// 最短路径与矩阵乘法
// 注意矩阵从0开始和从1开始的区别
// 定义矩阵的行和列从0开始
// 矩阵的表示方式，利用动态二维数组实现
#include "all_pair_shortest_path.h"

// 假定l和w的顶点个数和矩阵的内容已设置好
// lquote 的内存已分配，并均设为INFINITE，lquote作为输出被修改
// 数据结构多用指针来表示？
// 注意该函数有3个邻接矩阵同时参与运算
// l 和 w能否指向相同的内存？ 视情况而定
void extend_shortest_paths(const AdjMat* l, AdjMat* lquote, const AdjMat* w)
{
    int i, j, k;
    int n = l->rows;
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    lquote->mat[i][j] = INFINITE;
	    for (k = 0; k < n; k++) {
		lquote->mat[i][j] = min(lquote->mat[i][j], 
					inf_add(l->mat[i][k], w->mat[k][j]));
	    }
	}
    }
    return lquote;
}
// 假定w已分配内存，设置了正确的值
AdjMat* slow_all_pair_shortest_path(const AdjMat* w)
{
    int i;
    int n = w->rows;
    AdjMat* l = copy_adjmat(w);
    AdjMat* lquote = make_adjmat(n);
    // 邻接矩阵序号的起点为0
    // 循环的次数为n-2
    for (i = 1; i < n-1; i++) {
	// tmp, l, w必须不能指向相同的内存
	// 每次调用都要创建新的内存，如何避免？
	// 传入3个参数，使内存循环利用
	extend_shortest_paths(l, lquote, w);
	swap(l, lquote);
    }
    free_adjmat(lquote);
    return l;
}

AdjMat* faster_all_pair_shortest_path(const AdjMat* w)
{
    int i;
    int n = w->rows;
    // 是否可以不拷贝，指向相同的内容？否
    AdjMat* l = copy_adjmat(w);
    AdjMat* lquote = make_adjmat(n);
#ifdef DEBUG
    DEBUGP("before");
    fflush(stdout);
#endif // DEBUG
    i = 1;
    // 循环执行n-2次
    while(i < n-1)
    {
	extend_shortest_paths(l, lquote, l);
	swap(l, lquote);
	i = 2 * i; // 防止i = 0
    }    
#ifdef DEBUG
    DEBUGP("after");
    fflush(stdout);
#endif // DEBUG
    free_adjmat(lquote);
    return l;
}
