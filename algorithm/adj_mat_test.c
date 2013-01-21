#include <stdio.h>
#include <stdlib.h>

#include "adj_mat.h"

int main(int argc, char *argv[])
{
    FILE* pFile;
    AdjMat* m;
    if (argc != 2)
    {
	printf("usage: %s dat_filename\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    if((pFile = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open %s\n", argv[1]);
	exit(EXIT_FAILURE);
    }
    m = construct_adjmat(pFile);
    print_adjmat(m);
    free_adjmat(m);    
    return 0;
}
