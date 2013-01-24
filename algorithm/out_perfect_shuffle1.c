#include <stdio.h>  
#include <stdlib.h>
	   
// print a array  
void PRline(unsigned int* s, int count)  
{  
     unsigned int* end = s + count;  
     while(s < end) printf("%u/t",*s++);  
     printf("/n");  
}  
	   
// (2^howmany - 1) can be divided by x  
// return value: i 
// 找到这样的i， 第 m 次洗牌的效果和第 m + i次洗牌的效果一样
unsigned int CalLoop( unsigned int x )  
{  
    int i;
     unsigned int val = 2ull;  
     unsigned int x1 = x + 1u;  
     unsigned int x2 = x - 1u;  
     for(i = 1; i <= x ; i ++, val<<=1 )  
     {  
	  while( val >= x1 ) val -= x;  
	  if( val == 1u ) return i;  
	  if( val == x2 ) return i << 1;  
     }  
     return 0;  
}  
	   
// calc (1<<pow2)%x  
unsigned int Mod( unsigned int pow2, unsigned int x )  
{  
     unsigned int temp = 1u;  
     while( pow2-- )  
     {  
	  temp<<=1;  
	  if( temp >= x ) temp -= x;  
     }  
     return temp;  
}  
	   
void WashPoker( unsigned int N, unsigned int k )  
{  
     unsigned int N2_1 = (N<<1) - 1u;  
     unsigned int *a = (unsigned int *)malloc((N2_1 + 1u) * sizeof(unsigned int));
     unsigned int i, spos, pos, temp, temp2;  
     // 初始化数组
     for( i = 0; i <= N2_1; i++ ) a[i] = i+1u;  
     temp = CalLoop( N2_1 );  
     // if( temp ) k = k - k / temp * temp; 
     if (temp) k = k % temp;
     for( i = 1; i < N2_1; i++ )  
     {  
	  if( a[i] == i + 1u )  
	  {  
	       spos = pos = i;  
	       temp = a[i];  
	       while(1)  
	       {  
		    pos =  Mod( k, N2_1 ) * pos % N2_1;  
		    if( pos == spos ) break;  
		    temp2 = a[pos];  
		    a[pos] = temp;  
		    temp = temp2;  
	       };  
	       a[spos] = temp;  
	  }  
     }  
     PRline( a, N<<1 );  
     free(a);
}  
	   
	   
	   
int main()  
{  
     while(1)  
     {  
	  printf("please input Number(N, k): ");  
	  unsigned int N, k;  
	  scanf("%u %u", &N, &k);  
	  if( N == 0) break;  
	  WashPoker( N, k );  
     }  
     return 0;  
}  

