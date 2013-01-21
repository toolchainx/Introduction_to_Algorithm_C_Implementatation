#include <stdio.h>
#include "transitive_closure.h"


AdjMat* transitive_closure(AdjMat* g)
{
    int i, j, k;
    int n = g->rows;
    AdjMat* t = make_adjmat(n);
    AdjMat* tquote = make_adjmat(n);
    for (i = 0; i < n; i++) {
	for (j = 0; j < n; j++) {
	    if (g->mat[i][j] != INFINITE)
	    {
		t->mat[i][j] = 1;
	    }
	    else
	    {
		t->mat[i][j] = 0;
	    }
	}
    }
    for (k = 0; k < n; k++) {
	for (i = 0; i < n; i++) {
	    for (j = 0; j < n; j++) {
		tquote->mat[i][j] = t->mat[i][j] | (t->mat[i][k] &
						    t->mat[k][j]);
	    }
	}
	swap(t, tquote);
	/* printf("\n"); */
	/* print_adjmat(t); */
    }
    free_adjmat(tquote);
    return t;
}

