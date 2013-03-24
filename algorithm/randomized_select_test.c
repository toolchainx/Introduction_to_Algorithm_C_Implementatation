#include <stdio.h>
#include "randomized_select.h"

int main(int argc, char *argv[])
{
    int i,cnt = 0, arr[1001], k, result;
    while (cnt != 6) {
	scanf("%d", &cnt);
	for (i = 1; i <= cnt; i++) {
	    scanf("%d", &arr[i]);
	}
	scanf("%d", &k);
	result = randomized_select(arr, 1, cnt, k);
	printf("%d\n", result);
	fflush(stdout);
    }
    return 0;
}
