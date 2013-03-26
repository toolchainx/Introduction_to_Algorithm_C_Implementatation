#include "direct_address_hash.h"


int* direct_address_hash_init(int n)
{
    return (int *)malloc(sizeof(int) * n);
}


int direct_address_hash_search(int* A, int k)
{
    return A[k];
}


void direct_address_hash_insert(int* A, int k)
{
    A[k] = k;
}

void direct_address_hash_delete(int* A, int k)
{
    A[k] = NILINT;
}

void direct_address_hash_dtor(int* A)
{
    free(A);
}
