#ifndef _DP_ACTIVITY_SELECTOR_H_
#define _DP_ACTIVITY_SELECTOR_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct Activity_tag
{
    int anum;
    int st;
    int ft;
}Activity;

int dp_activity_selector(Activity* ap, int cnt);
void activity_set_output(Activity*** S, Activity* ap, int cnt);
void activity_solutions_output(int* C, Activity*** S, Activity* ap, int cnt, int i, int j);
#endif /* _DP_ACTIVITY_SELECTOR_H_ */
