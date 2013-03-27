#include "radix_sort.h"
#include "include/require.h"

#define length(A) ((sizeof(A))/(sizeof(A[0])))
int main(int argc, char *argv[])
{
    int A[] = {2, 5, 3, 0, 2, 3, 0, 3,1000, -99999,
	       -1000, 100000, 5999,499999, 6222,INT_MAX, INT_MIN};
    long a = (long)INT_MAX;
    long b =  (long)INT_MIN;
    unsigned int c = a - b;
    printf("%u\n", c);
    radix_sort(A, length(A));
    array_print(A, length(A));
    return 0;
}
