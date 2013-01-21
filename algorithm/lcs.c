#include <stdio.h>

#define M 102
#define N 102
#define length(array)  (sizeof(array)/sizeof(array[0]))
// c[i][j] 包含的是X 和Y的相似度

int c[M][N]={{0}};

typedef enum{GeneA,GeneC, GeneG, GeneT, GeneS} gene;

int geneTable[5][5] = {{5, -1, -2, -1, -3},
		       {-1, 5, -3, -2, -4},
		       {-2, -3, 5, -2, -2},
		       {-1, -2, -2, 5, -1},
		       {-3, -4, -2, -1, 0}};
int maxSimilarity(int a, int b, int c)
{
    if(a > b)
    {
	if(a > c)
	{
	    return a;
	}
	else 
	{
	    return c;
	}
    }
    else if(b > c)
    {
	return b;
    }
    else
    {
	return c;
    }
}

int calcSimilarity(gene up, gene down)
{
    /* if(up == GeneS && down == GeneS) */
    /* { */
    /* 	printf("up == GeneS and down == GeneS\n"); */
    /* 	return; */
    /* } */
    return geneTable[up][down];    
}
// X 和 Y 从 1开始计算
int lcs_similarity(gene *X, gene *Y, int lengthX, int lengthY)
{
    int m = lengthX;
    int n = lengthY;
    int i, j;
    c[0][0] = 0;
    for(i = 1; i <=m; i++)
    {
	int k;
	c[i][0] = 0;
	for(k = 1; k <= i; k++)
	{
	    c[i][0] += calcSimilarity(X[k], GeneS);
	}
    }
    for(j = 1; j <= n; j++)
    {
	c[0][j] = 0;
	int k;
	for(k = 1; k <= j; k++)
	{
	    c[0][j] += calcSimilarity(GeneS, Y[k]);
	}
    }
    for(i = 1; i <= m; i++)
    {
	for(j = 1; j <= n; j++)
	{
	    c[i][j] = maxSimilarity(c[i][j-1] + calcSimilarity(GeneS, Y[j]),
				    c[i-1][j] + calcSimilarity(X[i], GeneS),
				    c[i-1][j-1] + calcSimilarity(X[i], Y[j]));

	}    
    }
    return c[m][n];
}
void charToGene(char cArray[], gene gArray[], int length)
{
    int i;
    for(i =0; i <length; i++)
    {
	switch (cArray[i])
	{
	case 'A':
	    gArray[i+1] = GeneA;
	    break;
	case 'C':
	    gArray[i+1] = GeneC;
	    break;
	case 'G':
	    gArray[i+1] = GeneG;
	    break;
	case 'T':
	    gArray[i+1] = GeneT;
	    break;
	}
    }
}
void print(gene *gArray, int length)
{
    int i;
    for(i = 0; i < length; i++)
    {
	printf("%d ", (int)gArray[i]);
    }
    printf("\n");
}
void printc(int cArray[M][N], int m, int n)
{
    int i,j;
    for(i = 0; i <= m; i++)
	for(j = 0; j <= n; j++)
	{
	    printf("c[%d, %d] == %d\n", i, j, cArray[i][j]);
	}
}
int main()
{
    int numCases;
    gene X[102], Y[102];
    char cX[102], cY[102];
    int lenX, lenY;
    int countCase;
    scanf("%d", &numCases);
    // fflush(stdin);
    // printf("input the genes sequences\n");
    // fflush(stdout);
    for(countCase = 0; countCase < numCases; countCase++)
    {
	int maxResemblance;
	scanf("%d %s", &lenX, cX);
	scanf("%d %s", &lenY, cY);
	charToGene(cX, X, lenX);
	charToGene(cY, Y, lenY);
	// print(X, lenX+1);
	// print(Y, lenY+1);
	// fflush(stdout);
	maxResemblance = lcs_similarity(X, Y, lenX, lenY);
	printf("%d\n", maxResemblance);
	// printc(c, lenX, lenY);
	// fflush(stdout);
    }
    return 0;    
}
