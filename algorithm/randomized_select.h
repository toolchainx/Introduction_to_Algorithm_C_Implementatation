#ifndef _RANDOMIZED_SELECT_H_
#define _RANDOMIZED_SELECT_H_


#include <stdlib.h>
#include <stdio.h>
#include "include/require.h"
#include "quick_sort.h"
#include "randomized_select.h"
// 顺序统计学，找出第i小的数
// 从p到r(包括r)之间随机选择一个数
int random(int p, int r);
int randomized_partition(int* arr, int p, int r);
int randomized_select(int* arr, int p, int r, int i);

#endif /* _RANDOMIZED_SELECT_H_ */
