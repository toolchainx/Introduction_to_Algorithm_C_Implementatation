#include "rand_quick_sort.h"
#define length(arr) (sizeof(arr)/(sizeof(arr[0])))

int main(void)
{
    int A[] = {1, 3, 5, 2, 9, 100, 6, 7, 10, 11,11,1, 3,2, 97};
    int length = length(A);
    printf("the length of array A is: %d\n", length);
    rand_quick_sort(A, 0, length - 1);
    array_print(A, length);
    return 0;
    
}
