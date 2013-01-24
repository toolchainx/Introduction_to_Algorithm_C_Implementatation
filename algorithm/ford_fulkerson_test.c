#include "ford_fulkerson.h"

int main(int argc, char *argv[])
{
    FILE *pFile, *pCapFile;
    int s, t, numVertices;
    AdjList* g = NULL;
    AdjMat *f, *c;
    if (argc != 5)
    {
	printf("usage: %s dat_filename cap_filename start end\n", argv[0]);
	exit(EXIT_FAILURE);
    }
    if((pFile = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open %s\n", argv[1]);
	exit(EXIT_FAILURE);
    }
    if((pCapFile = fopen(argv[2], "r")) == NULL)
    {
	printf("can't open %s\n", argv[2]);
	exit(EXIT_FAILURE);
    }
    sscanf(argv[3], "%d", &s);
    sscanf(argv[4], "%d", &t);
    if (s == t)
    {
	printf("the start point is the same as the end point, exit\n");
	exit(EXIT_FAILURE);
    }
    // 构建不带权重的图
    g = construct_adjlist(argv[1], g, &numVertices);
    print_adjlist(g, numVertices);
    c = construct_param_adjmat(pCapFile, 0, 0);
    print_adjmat(c);
    f = make_param_adjmat(numVertices, 0, 0);
    print_adjmat(f);
    printf("ford_fulkerson\n");
    fflush(stdout);
    ford_fulkerson(g, numVertices, s, t, f, c);
    print_adjmat(f);
    free_adjmat(f);
    free_adjmat(c);
    free_adjlist(g, numVertices);

    return 0;
}
