#include "fib_heap.h"


// test the Fibonacci heap
int main(int argc, char *argv[])
{
    int arr1[NUMARRAY] = {23, 7, 21, 3};
    // int arr1[NUMARRAY] = {3, 7, 23, 21, 24, 18, 52, 17};
    int arr2[NUMARRAY] = {17, 24, 18, 52};
    // ¹¹½¨¶Ñ
    FibHeap h1 = fib_heap_construct(arr1, sizeof(arr1)/sizeof(*arr1));
    printf("h1:\n");
    // fib_heap_extract_min(h1);
    fib_heap_root_print(h1->min);
    FibHeap h2 = fib_heap_construct(arr2, sizeof(arr2)/sizeof(*arr2));
    printf("h2:\n");
    fib_heap_root_print(h2->min);
    FibHeap h = fib_heap_union(h1, h2);
    printf("h:\n");
    fib_heap_root_print(h->min);
    RootTblPtr min = fib_heap_extract_min(h);
    printf("min = %d\n", min->key);
    fib_heap_root_print(h->min);
    min = fib_heap_minimum(h);
    fib_heap_decrease_key(h, min, 5);
    printf("after decreased key h:\n");
    fib_heap_root_print(h->min);
    fib_heap_delete(h, min);
    printf("after delete key h:\n");
    fib_heap_root_print(h->min);
    printf("after delete key 52 h:\n");
    fib_heap_root_print(h->min);
    return 0;
}
