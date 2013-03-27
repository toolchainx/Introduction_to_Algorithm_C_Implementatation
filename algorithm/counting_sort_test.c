#include "counting_sort.h"
#include "include/require.h"
#define length(A) ((sizeof(A))/(sizeof(A[0])))
int main(int argc, char *argv[])
{
    int A[] = {2, 5, 3, 0, 2, 3, 0, 3};
    counting_sort(10, A, length(A));
    array_print(A, length(A));
    return 0;
}
