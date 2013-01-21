#include "johnson.h"

int main(int argc, char *argv[])
{
    FILE* pFile;
    int numVertices;
    adj_list* g = NULL;
    AdjMat* d;
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
    g = construct_weighted_adj_list(argv[1], g, &numVertices);
    adj_output(g, numVertices);
    printf("johnson\n");
    fflush(stdout);
    d = johnson(g, numVertices);
    print_adjmat(d);
    free_adjmat(d);
    freeAdjList(g, numVertices);
    return 0;
}
