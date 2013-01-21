#include <stdio.h>
#include "adj_table.h"
#include "dfs.h"

static void swap(int arr[], int i, int j)
{
    int tmp;
    tmp = arr[i];
    arr[i] = arr[j];
    arr[j] = tmp;
}

int main(int argc, char *argv[])
{
    int f[] = {5, 7, 8, 9, 4, 2, 1};
    int min, i,j;
    for (i = 0; i < 6; i++) {
	min = i;
	for (j = i+1; j < 7; j++) {
	    if (f[min] > f[j])
	    {
	        min = j;
	    }
	}
	swap(f, i, min);
	print_array("f", f, 7);
	printf("\n");
    }
    print_array("f", f, 7);
    return 0;
}
