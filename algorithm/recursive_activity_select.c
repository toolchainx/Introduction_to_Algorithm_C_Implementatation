#include "recursive_activity_select.h"


int recursive_activity_select(Activity* A, int i, int n)
{
    int m = i + 1;
    while (m < n && A[m].st < A[i].ft) {
	m++;
    }
    if (m < n)
    {
	printf("%d, st: %d, ft: %d\n", m, A[m].st, A[m].ft);
	fflush(stdout);
	return 1 + recursive_activity_select(A, m, n);
    }
    else{
	return 0;
    }
}
