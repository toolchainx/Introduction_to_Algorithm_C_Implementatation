#include "floyd_warshall.h"



AdjMat* floyd_warshall(AdjMat* w)
{
    int i, j, k;
    int n = w->rows;
    // d 和 dquote能不能指向相同的内存？ 否
    AdjMat* d = copy_adjmat(w);
    AdjMat* dquote = make_adjmat(w->rows);
    for (k = 0; k < n; k++) {
	for (i = 0; i < n; i++) {
	    for (j = 0; j < n; j++) {
		dquote->mat[i][j] = min(d->mat[i][j],
		                        inf_add(d->mat[i][k], d->mat[k][j]));
	    }
	}
	// 交换d和dquote的指针 宏实现
	swap(d, dquote);
    }
    free_adjmat(dquote);
    return d;
}
