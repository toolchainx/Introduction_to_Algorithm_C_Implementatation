#ifndef _BUCKET_SORT_H_
#define _BUCKET_SORT_H_
#include "include/require.h"
typedef struct Blist_tag {
    int key;
    struct Blist_tag* next;
} BNode;

void bucket_sort(int* A, int n);
#endif /* _BUCKET_SORT_H_ */
