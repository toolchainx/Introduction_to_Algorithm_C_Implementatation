#include "include/require.h"
#include "direct_address_hash.h"
#define length(a)  (sizeof(a)/sizeof(a[0]))

int main(int argc, char *argv[])
{

    int input[] = {10,21,45,22,7,2,67,19,13,45,12,  11,18,16,17,100,201,20,101};
    // find the max number
    int max_num = input[0];
    int len = length(input);
    int i;
    int* arr;
    for (i = 0; i < len; i++) {
	if (input[i] > max_num)
	{
	    max_num = input[i];
	}
    }
    arr = direct_address_hash_init(max_num);
    for (i = 0; i < len; i++) {
	direct_address_hash_insert(arr, input[i]);
    }

    dprint(direct_address_hash_search(arr, 10));
    direct_address_hash_delete(arr, 10);
    dprint(direct_address_hash_search(arr, 10));
    direct_address_hash_search(arr, 99);
    direct_address_hash_insert(arr, 99);
    dprint(direct_address_hash_search(arr, 99));
    dprint(direct_address_hash_search(arr, 11));
    direct_address_hash_dtor(arr);

    return 0;
}
