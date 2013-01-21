#include <stdio.h>
#include <stdlib.h>
#define N 10
#define Y 105
// iterate call to find the selected objects
/********************
 j=m;
    for(i=row-1;i>0;i--)
    {
        if(value[i][j]>value[i-1][j])
        {
            c[i]=1;
            j-=w[i];
        }
    }
*/
// tail call
void getTheObj(int totval[N+1][Y+1], int index1, int index2, int w[N])
{
  if(index1 < 0)
    {
      printf("end.\n");
      exit(0);
    }
  if(totval[index1][index2] < totval[index1 +1][index2])
    {
      printf("%d\n", index1+1);
      getTheObj(totval, index1 -1, index2-w[index1+1], w);
    }
  else
    {
      getTheObj(totval, index1 -1, index2, w);
    }
}
int main(void)
{
  int w[N+1] = {0,12, 16, 24, 7, 29, 32, 5, 43, 31, 1}, v[N+1] = {0,11,16,15,9,24,25,3,32,41,7};
  int m;  // 背包的重量
  int totval[N+1][Y+1] = {0}; // 在前N种物品中选择所能达到的最高价值
  int i, j, k;
  for (i = 0; i < N+1; i++)
    {
      totval[i][0] = 0;
    }
  for (i = 0; i < Y+1; i++)
    {
      totval[0][i] = 0;
    }
  for (i = 1; i < N + 1; i++)
    {
      m = Y;
      while(m >= 0)
	{
	  if (i == 1)
	    printf("test\n");
	  if ((m >= w[i])&&(totval[i-1][m] > v[i] + totval[i-1][m-w[i]]) || m < w[i])
	    {
	      totval[i][m] = totval[i-1][m];
	    }
	  else 
	    {
	      totval[i][m] = v[i] + totval[i-1][m - w[i]];
	    }
	  m--;
	}
    }
  // 输出所有的total value
  printf("  N----  Y-----  Total value\n");
  for (i = 0; i < N+1; i++)
    for(j = 0; j < Y+1; j++)
      {
	if (totval[i][j] > 0)
	  printf("%3d----%3d-----%3d\n", i, j, totval[i][j]);
      } 
  // 输出最高价值和选择的物品
  printf("the total value of the knapsack is %d\n", totval[N][Y]);
  getTheObj(totval, N-1, Y, w);
}
