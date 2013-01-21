#include <stdio.h>
// 数组A从1开始计数

int heap_size;

int length(int A[])
{
    return 7;
}

int parent(int i)
{
    return i/2;
}

int left(int i)
{
    return 2*i;
}

int right(int i)
{
    return 2*i + 1;
}

void swap(int A[], int m, int n)
{
    int tmp = A[m];
    A[m] = A[n];
    A[n] = tmp;
}


void max_heapify(int A[], int i)
{
    int largest;
    int l = left(i);
    int r = right(i);
    if (l <= heap_size && A[i] < A[l])
    {
	largest = l;
    }
    else
    {
	largest = i;
    }

    if (r <= heap_size && A[largest] < A[r])
    {
	largest = r;
    }
    if (largest != i)
    {
	swap(A, largest, i);
	max_heapify(A, largest);
    }
}

void build_max_heap(int A[])
{
    heap_size = length(A);
    int i;
    for(i = heap_size/2; i > 0; i--)
    {
	max_heapify(A, i);
    }
}

void printArray(int A[])
{
    int i;
    /* printf("%d", (int)sizeof(A)); */
    /* printf("%d", (int)sizeof(A[0])); */
    /* printf("the length of size A is %d\n",(int)(sizeof(A)/sizeof(A[0]))); */

    for(i = 1; i <= length(A); i++)
    {
	printf("%d ", A[i]);
    }
    printf("\n");
}

void heap_sort(int A[])
{
    int i;
    build_max_heap(A);
    for(i = length(A); i > 0; i--)
    {
	swap(A, 1, i);
	heap_size = heap_size - 1;
	max_heapify(A, 1);
    }
}

int main()
{
    int array[] = {0, 13, 14, 16, 19, 67, 34, 45};
    heap_sort(array);
    printArray(array);
    return 0;
}

