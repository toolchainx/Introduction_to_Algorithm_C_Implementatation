// 开放寻址，线性探查法
// 利用数组来实现
// 只有插入和查找的实现，没有删除操作
#include "open_address_linear_hash.h"
#include <stdio.h>
#include <stdlib.h>


int* open_address_linear_hash_init(int n)
{
    int* A = (int*)malloc(sizeof(int) * n);
    int i;
    for (i = 0; i < n; i++) {
	A[i] = NILINT;
    }
    return A;
}

void open_address_linear_hash_dtor(int* A)
{
    free(A);
}

int open_address_linear_hash_insert(int* A, int n, int k)
{
    int i = 0;
    while(i < n)
    {
        int j = (k + i)%n;
	if (A[j] == NILINT)
	{
	    A[j] = k;
	    return j;
	}
	i++;
    }
    printf("error: the hashset is full!\n");
    fflush(stdout);
    exit(EXIT_FAILURE);
}

int open_address_linear_hash_search(int* A, int n, int k)
{
    int i = 0;
    while(i < n)
    {
	int j = (k + i)%n;
	if (A[j] == NILINT)
	{
	    printf("the number: %d is not in the hashset\n", k);
	    return NILINT;
	}
	else if (A[j] == k)
	{
	    return j;
	}
	else
	{
	    i++;
	}
    }
    printf("the number: %d is not in the hashset\n", k);
    return NILINT;
}

void open_address_linear_hash_output_test(int* A , int n)
{
    array_print(A, n);
}
