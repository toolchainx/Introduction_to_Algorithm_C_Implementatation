#include "counting_sort.h"
#include <stdio.h>
#include <stdlib.h>


void counting_sort(int k, int*A, int n)
{
    int* B = (int*)malloc(sizeof(int) * n);
    // allocate for c array and clear to zero
    int* C = (int*)calloc(k, sizeof(int));
    int i, j;
    // C[i] has the cnt of i
    for (i = 0; i < n; i++) {
	C[A[i]] = C[A[i]] + 1;
    }
    // C[i] has the cnt of number that <= i
    for (j = 1; j < k; j++) {
	C[j] =  C[j] + C[j-1];
    }
    for (i = n-1; i >= 0; i--) {
	B[C[A[i]] - 1] = A[i];
	C[A[i]]--;
    }
    for (i = 0; i < n; i++) {
	A[i] = B[i];
    }    
    free(B);
    free(C);
}
