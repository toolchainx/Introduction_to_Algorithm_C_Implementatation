#include "radix_sort.h"

unsigned int getDigit(unsigned int a, int i);
void nn_radix_sort(unsigned int* A, int n);
// choose the counting sort as the stable sort sub fuction
// sort the int data 32bit divided into 4 parts, each parts has 8bits
// how to consider the positive int and negative int?
void radix_sort(int* A, int n)
{
    // find the minimum negative number
    long min = A[0];
    int i;
    for (i = 1; i < n; i++) {
	if (min > A[i])
	{
	    min = A[i];
	}
    }
    if (min < 0)
    {
	unsigned int* B = (unsigned int*)malloc(sizeof(unsigned int) * n);
	for (i = 0; i < n; i++) {
	    long tmp = A[i];
	    B[i] = tmp - min;
	}
	nn_radix_sort(B, n);
	for (i = 0; i < n; i++) {
	    long tmp = B[i];
	    A[i] = tmp + min;
	}
	free(B);
    }
    else
    {
	nn_radix_sort((unsigned int*)A, n);
    }	
}
void nn_radix_sort(unsigned int* A, int n)
{
    int i;
    unsigned int* B = (unsigned int*)malloc(sizeof(unsigned int) * n);
    // k is 256
    unsigned int* C = (unsigned int*)calloc(256, sizeof(unsigned int));
    for (i = 0; i < 4; i++) {
	int j, k;
	// clear C array
	memset(C, 0, 256*sizeof(unsigned int));
	for (j = 0; j < n; j++) {
	    C[getDigit(A[j], i)]++;
	}
	// start from 1
	for (k = 1; k < 256; k++) {
	    C[k] += C[k-1];
	}
	for (j = n-1; j >= 0; j--) {
	    B[C[getDigit(A[j], i)] -1] = A[j];
	    C[getDigit(A[j], i)]--;
	}
	for(j = 0; j < n; j++)
	{
	    A[j] = B[j];
	}
    }
    free(B);
    free(C);
}

unsigned int getDigit(unsigned int a, int i)
{
    unsigned int curBitsTpt = 0xFF << i*8;
    return (a&curBitsTpt) >> i*8;    
}
