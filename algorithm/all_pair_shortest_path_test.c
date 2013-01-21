#include <stdio.h>
#include <stdlib.h>

#include "all_pair_shortest_path.h"



int main(int argc, char *argv[])
{
    FILE* pFile;
    AdjMat *m, *l;
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
    printf("slow all pair shortest path\n");
    l = slow_all_pair_shortest_path(m);
    print_adjmat(l);
    free_adjmat(l);
    printf("faster all pair shortest path\n");    
    l = faster_all_pair_shortest_path(m);
    print_adjmat(l);
    free_adjmat(l);
    free_adjmat(m);    
    return 0;
}
