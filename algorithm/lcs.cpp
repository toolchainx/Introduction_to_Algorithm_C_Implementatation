//最长公共子序列_动态规划
//算法导论P208 15.4
//POJ1080

//状态方程：
//如果str[]

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

const int MaxStrLen = 105;

//将字符转化为索引，读取score表
int char2int(char c)
{
    switch(c)
    {
    case 'A':
	return 0;
	break;
    case 'C':
	return 1;
	break;
    case 'G':
	return 2;
	break;
    case 'T':
	return 3;
	break;
    case '-':
	return 4;
	break;
    default:
	return -1;
	break;
    }
}

//score数组
int scores[5][5] = { {5,-1,-2,-1,-3},
		     {-1,5,-3,-2,-4},
		     {-2,-3,5,-2,-2},
		     {-1,-2,-2,5,-1},
		     {-3,-4,-2,-1,10}};

int main()
{
    
    string s;
    std::cout << "hello" << endl;
    int N;
    cin >> N;
    while(N--)
    {
	int len1,len2;
	string str1,str2;
	cin>> len1 >> str1 >> len2 >>str2;

	//c[i][j]记录str1的前i个字符与str2的前j个字符的相似度
	int c[MaxStrLen][MaxStrLen];
	//初始化
	memset(c,0,sizeof(c));
	for (int i = 1;i <= len1;++i)
	{
	    c[i][0] = c[i - 1][0] + scores[char2int(str1[i - 1])][char2int('-')];
	}
	for (int j = 1;j <= len2;++j)
	{
	    c[0][j] = c[0][j - 1] + scores[char2int('-')][char2int(str2[j - 1])];
	}

	for (int i = 1;i <= len1;++i)
	{
	    for (int j = 1;j <= len2;++j)
	    {
		int temp1 = c[i - 1][j - 1] + scores[char2int(str1[i - 1])][char2int(str2[j - 1])];
		int temp2 = c[i - 1][j] + scores[char2int(str1[i - 1])][char2int('-')];
		int temp3 = c[i][j - 1] + scores[char2int(str2[j - 1])][char2int('-')];
		c[i][j] = max(temp1,max(temp2,temp3));
	    }
	}

	cout << c[len1][len2] << endl;
    }
}
