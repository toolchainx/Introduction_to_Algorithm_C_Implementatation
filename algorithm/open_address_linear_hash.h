#ifndef _OPEN_ADDRESS_LINEAR_HASH_H_
#define _OPEN_ADDRESS_LINEAR_HASH_H_
#include "include/require.h"
#include <limits.h>
#include <stdio.h>
#define NILINT  INT_MAX

void open_address_linear_hash_output_test(int* A, int n);
int open_address_linear_hash_search(int* A, int n, int k);
int open_address_linear_hash_insert(int* A, int n, int k);
void open_address_linear_hash_dtor(int* A);
int* open_address_linear_hash_init(int n);

#endif /* _OPEN_ADDRESS_LINEAR_HASH_H_ */
