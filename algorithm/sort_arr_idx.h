#ifndef _SORT_ARR_IDX_H_
#define _SORT_ARR_IDX_H_

#include "include/require.h"
#include <stdlib.h>

typedef struct tagValIdxPair
{
    int val;
    int idx;
} ValIdxPair;
void rvs_arr(int* arr, int num);
void sort_arr_idx(const int* arr, int num, int* seq);



#endif /* _SORT_ARR_IDX_H_ */
