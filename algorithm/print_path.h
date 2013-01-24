#ifndef _PRINT_PATH_H_
#define _PRINT_PATH_H_

#include "include/require.h"
#include "adj_table.h"
#include <stdio.h>

void print_arr(int point);

void print_path(AdjList* pAdjl, int* parent, int start, int end);

#endif /* _PRINT_PATH_H_ */
