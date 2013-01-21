#ifndef _PRINT_PATH_H_
#define _PRINT_PATH_H_

#include "include/require.h"
#include "adj_table.h"
#include <stdio.h>

void print(int point);

void print_path(adj_list* pAdjl, int* parent, int start, int end);

#endif /* _PRINT_PATH_H_ */
