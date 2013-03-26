#include "open_address_linear_hash.h"
#define length(A) ((sizeof(A))/(sizeof(A[0])))

int main(int argc, char *argv[])
{
    int input[] = {10,21,45,22,7,2,67,19,13,45,12,  11,18,16,17,100,201,20,101};
    int len = length(input);
    int i;
    int* A = open_address_linear_hash_init(len);
    for (i = 0; i < len; i++) {
	open_address_linear_hash_insert(A, len, input[i]);
    }
    open_address_linear_hash_output_test(A, len);
    printf("\n");
    for (i = 0; i < len; i++) {
	int j = open_address_linear_hash_search(A, len, input[i]);
	printf("the address of %d is %d\n", input[i], j);
	printf("\n");
    }

    open_address_linear_hash_dtor(A);
    return 0;
}
