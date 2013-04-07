#include "dp_activity_selector.h"


// calculate the S[i, j] first
// allocate an array(the element of the array point to the activitis in S[i, j])
// for each S[i, j]
// then the C[i, j]
int dp_activity_selector(Activity* ap, int cnt)
{
    int max_cpt_cnt;
    int i, j, k;
    Activity*** S = (Activity***)calloc((cnt ) * (cnt ),  sizeof(Activity **));
    int* C = (int *)calloc((cnt ) * (cnt ), sizeof(int));
    for (i = 0; i < cnt ; i++) {
	for (j = 0; j < cnt; j++) {
	    // calcualte the S[i, j]
	    int m = 0;
	    *(S + i*(cnt) + j) = (Activity **)calloc(cnt, sizeof(Activity*));
	    for (k = 1; k < cnt-1; k++) {
		if(ap[k].st >= ap[i].ft &&
		   ap[k].ft <= ap[j].st)
		{
		    // insert ap[k] to the S[i, j] array
		   (*(S + i*(cnt) + j))[m++] = ap + k;
		}
	    }
	}
    }
    // test the S[i, j] output it
    activity_set_output(S, ap, cnt); 
    for (j = 0; j < cnt; j++) {
	for(i = 0; i < j;i++){
	    // calculate the C[i, j]
	    int max_sub_cnt = 0;
	    Activity* alp;
	    for (k = 0; (*(S + i*(cnt) +j))[k] != NULL; k++) {
		int tmp_sub_cnt;
		alp = (*(S + i*(cnt) +j))[k];
		tmp_sub_cnt = *(C + i*(cnt ) + alp->anum) + *(C + alp->anum *(cnt ) + j) + 1;
		if (max_sub_cnt < tmp_sub_cnt)
		{
		    max_sub_cnt = tmp_sub_cnt;
		}
	    }
	    *(C + i*(cnt ) + j) = max_sub_cnt;
	}	
    }
    // output all the solutions
    activity_solutions_output(C, S, ap, cnt, 0, cnt-1);
    max_cpt_cnt = *(C + cnt-1);
    for (i = 0; i < cnt; i++) {
	for (j = 0; j < cnt; j++) {
	    free(*(S + i*cnt + j));
	    *(S + i*cnt + j) = NULL;
	}
    }
    free(S);
    free(C);
    return max_cpt_cnt;
}

void activity_set_output(Activity*** S, Activity* ap, int cnt)
{
    int i, j, k;
    for (i = 0; i < cnt; i++) {
	for (j = 0; j < cnt; j++) {
	    printf("S[%d, %d]\n", i, j);
	    printf("start time: %d\n", ap[i].ft);
	    printf("finish time: %d\n", ap[j].st);
	    for (k = 0; (*(S + i * cnt + j) != NULL) && ((*(S + i * cnt + j))[k] != NULL) ; k++) {
		Activity* ap = (*(S + i * cnt + j))[k];
		printf("num: %d st: %d ft: %d ",ap->anum, ap->st, ap->ft);
	    }
	    printf("\n");
	    fflush(stdout);
	}
    }
}   
void activity_solutions_output(int* C, Activity*** S, Activity* ap, int cnt, int i, int j)
{
    static int count = 0;
    int k;
    for (k = 0; *(S + i*cnt + j) != NULL && (*(S + i*cnt + j))[k] != NULL; k++) {
	Activity* aptmp = (*(S + i*cnt + j))[k];
	if ((*(C + i*cnt + j)) == (*(C + i*cnt + aptmp->anum) + *(C + aptmp->anum*cnt + j) + 1))
	{
	    if (i == 0 && j == cnt -1 )
	    {
		printf("the %d solutions: \n",  count++);
	    }
	    printf("%d ->\n", aptmp->anum);
	    printf("  ->");
	    activity_solutions_output(C, S, ap, cnt, i, aptmp->anum);
	    printf("  ->");
	    activity_solutions_output(C, S, ap, cnt, aptmp->anum, j);
	    printf("  <-\n");
	}
    }

}
