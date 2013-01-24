//By LYLtim
 
#include<stdio.h>
 
const unsigned upperlim = (1 << 8) - 1;
unsigned ans = 0;
     
void DFS(unsigned row, unsigned ld, unsigned rd)
{
    if (row != upperlim) {
	unsigned pos = upperlim & ~(row | ld | rd), p;
	while (pos) {
	    p = pos & -pos;
	    pos -= p;
	    DFS(row | p, (ld | p) << 1, (rd | p) >> 1);
	}
    } else ans += 1;
}
 
int main(void)
{
    DFS(0, 0, 0);
    printf("%d\n", ans);
}
