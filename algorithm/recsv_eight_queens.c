/** 
 * eight queens puzzle
 * 递归算法
 * 1，为了确定第n列皇后的位置
 * 必须先确定第n-1列皇后的位置
 * 由此形成递归
 * 2，当第n列没有满足条件的摆放位置时
 * 开始回溯，寻找第n-1列满足条件位置的
 * 下一个位置（由chess[8]作为全局变量来保存状态)
 * 修改chess[n-1]，将第n列（包括n以后的位置置为-1)继续寻找第n列的摆放位置
 * 由此形成了另一个递归程序
 * 注意边界条件值
 * 
 */
#include <stdio.h>
int chess[8];

// chess[8] 所有的位置初始化为-1
typedef enum{ false, true} bool;
bool posOK(int i, int n)
{
    int queenPosIndex;
    for(queenPosIndex = 0; queenPosIndex < n; queenPosIndex++)
    {
	// 判断第n列的皇后放在第i个位置对第queenPosIndex来说是否符合要求
	// for 循环也相当于一个判断语句
	if (chess[queenPosIndex] == i)
	{
	    return false;
	}
	else if((i - chess[queenPosIndex] == n - queenPosIndex) ||
		(i + n == queenPosIndex + chess[queenPosIndex]))
	{
	    return false;
	}     
    }
    return true;
}
void setQueenPos(int n);
bool change(int n)
{
    if ( n == -1)
    {
	return false;
    }
    //查找第n个皇后的摆放位置
    int queenPos;
    if((queenPos = (find(n))) != -1)
    {
	// 将满足条件的位置放置在棋盘中
	chess[n] = queenPos;
	// 将第n列以后的皇后位置全部置为-1
	setQueenPos(n);
	return true;
    }
    return false;
}
// 每次执行find查找的都是一个新的满足条件的chess[8]
int find(int n)
{
    // 判断第n列的第i个位置是否可以放置
    int i;
    while (1)
    {
	// find(0)
	// chess[0] + 1 == 2
	for(i = chess[n] + 1; i < 8; i++)
	{
	    if (posOK(i, n))
	    {
		return i;
	    }
	}

	if (!change(n-1))
      	{
	    return -1;
      	}
    }
    return -1;
}
void setQueenPos(int n)
{
    int i;
    for(i = n+1; i < 8; i++)
    {
	chess[i] = -1;
    }
}
// 如果所有的位置都尝试过，没有找到
// 修改前n-1列，找到另一个满足条件的eightQueen(n-1)
// 如何区分两个满足条件的eightQueen(n-1)?
// 回退到eightQueenNext(n-1)
// while 语句有问题
// 每次执行eightQueen(n-1) 找到下一个满足条件的摆放位置
// 利用回溯查找
// 思考如何建立回退的模型
// 建立失败模型
// while(failed)
// {
//   回溯；
//   前进；
// }
// 成功：打印输出结果;
bool eightQueen(int n)
{
    if (n == -1)
    {
	return true;
    }
    else
    {
	if(eightQueen(n-1))
	{
	    //查找第n个皇后的摆放位置
	    int queenPos;
	    if((queenPos = (find(n))) != -1)
	    {
		// 将满足条件的位置放置在棋盘中
		chess[n] = queenPos;
		// 将第n列以后的皇后位置全部置为-1
		// if (n == 7) 打印输出结果
		setQueenPos(n);
		return true;
	    }
	}
	return false;
    }
}

void printChessboard()
{
    int i;
    for(i = 0; i < 8; i++)
    {
	fprintf(stdout, "(%d, %d) ", i+1, chess[i] + 1);
	fflush(stdout);
    }
    fprintf(stdout, "\n");
    fflush(stdout);
}
void setChess()
{
    int i;
    for(i = 0; i < 8; i++)
    {
	chess[i] = -1;
    }
}

int main()
{
    int num;
    int numOfMethod =0;
    fprintf(stdout, "input the number of queen: \n");
    fflush(stdout);
    fscanf(stdin,"%d", &num);
    fflush(stdin);
    setChess();
    while(num !=  -1)
    {
    	setChess();
    	eightQueen(num);
    	printChessboard();
    	fprintf(stdout, "input the number of queen: \n");
    	fflush(stdout);
    	fscanf(stdin, "%d", &num);
    	fflush(stdin);
    }
    /* setChess(); */
    /* if (eightQueen(7)) */
    /*   { */
    /*     printChessboard(); */
    /*     numOfMethod++; */
    /*   } */
    /* int queenPos; */
    /* while((queenPos = find(7)) != -1) */
    /*   { */
    /*     chess[7] = queenPos; */
    /*     printChessboard(); */
    /*     numOfMethod++; */
    /*   } */
    /* printf("the number of method is: %d\n", numOfMethod); */
}

