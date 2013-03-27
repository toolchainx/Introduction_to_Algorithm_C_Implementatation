#include "bucket_sort.h"
#define length(A) ((sizeof(A))/(sizeof(A[0])))
int main(int argc, char *argv[])
{

    int A[] = {78, 17, 39, 26, 72, 94, 21, 12, 23, 68};
    bucket_sort(A, length(A));
    array_print(A, length(A));
    return 0;
}
