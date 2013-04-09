#include "huffman_coding.h"
#include <stdlib.h>

qNode* A[MAX_SIZE];
int len = 0;

int main(int argc, char *argv[])
{
    FILE* pf;
    char c;
    int key;
    int i,count;
    if (argc != 2)
    {
	printf("usage: %s data filenmae", argv[0]);
	exit(EXIT_FAILURE);
    }
    if ((pf = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open file\n");
	exit(EXIT_FAILURE);
    }
    fscanf(pf, "%d\n", &count);
    A[0] = NULL;
    for (i = 0; i < count; i++)
    {
	fscanf(pf, "%c %d\n", &c, &key);
	qNode* x = create_node(c, key);
	min_queue_insert(A,&len, x);
	min_queue_output(A, len);
    }
    qNode* pqn = huffman(A, len);
    btree_output(pqn);
    dict* dt = huffman_genDict(pqn, len);
    dict_output(dt, len);    
    fclose(pf);
    return 0;
}
