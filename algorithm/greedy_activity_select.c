#include "greedy_activity_select.h"


// assume that the activities is sort by the ft time in ascending order.
int greedy_activity_select(Activity* ap, int length)
{
    int i = 0, m = i + 1, count = 0;
    while (m < length) {
	if (ap[m].st > ap[i].ft)
	{
	    printf("%d, st: %d, ft: %d\n", ap[m].anum,ap[m].st, ap[m].ft);
	    i = m;
	    count++;
	}
	m++;
    }
    return count;
}
