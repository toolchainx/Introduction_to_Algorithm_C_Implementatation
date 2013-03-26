// 实现随机快排算法
#include <stdlib.h>
#include "rand_quick_sort.h"



int rand_partition(int A[], int p, int r)
{
    int rand_pivot = (r - p) * rand()/RAND_MAX + p;
    dprint(r);
    dprint(p);
    dprint(rand_pivot);
    array_swap(A, rand_pivot, r);
    return partition(A, p, r);
}

void rand_quick_sort(int A[], int p, int r)
{
    int q;
    // when the recursion end?
    if (p >= r)
    {
	return;
    }
    q = rand_partition(A, p, r);
    dprint(q);
    rand_quick_sort(A, p, q-1);
    rand_quick_sort(A, q+1, r);
}


void test()
{
    
}
