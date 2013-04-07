#include "dp_activity_selector.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main(int argc, char *argv[])
{
    Activity* ap;
    FILE* pf;
    int at_cnt;
    int max_cpt_at;
    int st;
    int ft;
    int i;
    if (argc != 2)
    {
	printf("usage:%s data filename", argv[0]);
	fflush(stdout);
    }
    if ((pf = fopen(argv[1], "r")) == NULL)
    {
	printf("can't open the data file %s: ", argv[1]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    fscanf(pf, "%d", &at_cnt);
    ap = (Activity* )malloc((at_cnt + 2)* sizeof(Activity));
    ap[0].anum = 0;
    ap[0].st = 0;
    ap[0].ft = 0;
    for (i = 1; i < at_cnt + 1; i++) {
	fscanf(pf, "%d", &st);
	fscanf(pf, "%d", &ft);
	ap[i].anum = i;
	ap[i].st = st;
	ap[i].ft = ft;	
    }
    ap[at_cnt + 1].anum = at_cnt + 1;
    ap[at_cnt + 1].st = INT_MAX;
    ap[at_cnt + 1].ft = INT_MAX;
    max_cpt_at = dp_activity_selector(ap, at_cnt + 2);
    printf("the max count of compatible activities is %d\n", max_cpt_at);
    free(ap);
    return 0;
}
