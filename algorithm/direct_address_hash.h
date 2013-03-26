#ifndef _DIRECT_ADDRESS_HASH_H_
#define _DIRECT_ADDRESS_HASH_H_
#include <limits.h>
#include <stdlib.h>

#define NILINT INT_MAX
int* direct_address_hash_init(int n);
void direct_address_hash_dtor(int* A);
void direct_address_hash_delete(int* A, int k);
void direct_address_hash_insert(int* A, int k);
int direct_address_hash_search(int* A, int k);

#endif /* _DIRECT_ADDRESS_HASH_H_ */
