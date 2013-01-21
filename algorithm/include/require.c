#include <stdio.h>
#include "require.h"



void array_swap(int A[], int m, int n)
{
    int tmp = A[m];
    A[m] = A[n];
    A[n] = tmp;
}

/* void list_print(List list) */
/* { */
/*     while (list) */
/*     { */
/* 	printf("%d ", list->value); */
/* 	list = list->next; */
/*     } */
/*     printf("\n"); */
/* } */

void array_print(int array[], int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	printf("array[%d] = %d\n", i, array[i]);
    }
}
