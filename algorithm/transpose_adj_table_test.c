#include <stdlib.h>
#include "transpose_adj_table.h"

int main(int argc, char *argv[])
{
    AdjList* pAdjl = NULL;
    int numVertices;
    if (argc != 2)
    {
	printf("input the data file\n");
	exit(EXIT_FAILURE);
    }
    pAdjl = construct_adjlist(argv[1], pAdjl, &numVertices);
    pAdjl = transpose_adj_table(pAdjl, numVertices);
    print_adjlist(pAdjl, numVertices);
    free_adjlist(pAdjl, numVertices);
    return 0;
}
