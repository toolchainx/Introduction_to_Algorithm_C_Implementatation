#ifndef _REQUIRE_H_
#define _REQUIRE_H_

// 在编写算法导论程序时，将要使用到的公共头文件
// 包括常用的调试打印语句，
// 常用的打印语句包括：
// 打印变量值的同时，打印该变量的符号
// 打印一个数组
// 打印一个链表中的值
// 交换两个变量中的值
// 交换数组或链表中两个索引的值
// 常用的宏
// 常用的枚举值
// 注意，该处处理的变量多为整型变量
#include <stdio.h>
#include <string.h>
#include <limits.h>

#define NIL NULL
// 用于自然数集的无效数值
#define NILVALUE -1
// 用于表示无穷的数，进行运算操作时，应特别处理
#define INFINITE INT_MAX
#define NINFINITE INT_MIN
// 定义min，注意其副作用
#define min(a, b) ((a) > (b))? (b):(a)
#define inf_add(a, b)  \
    ((a) == INFINITE || (b) == INFINITE)? \
    INFINITE:((a) + (b))
    
#define inf_sub(a, b) \
    ((a) == INFINITE || (b) == INFINITE)? \
    INFINITE:((a) - (b))

#define dprint(expr) printf(#expr " = %d\n", expr)

#ifdef DEBUG
#define DEBUGP(x, args ...) fprintf(stderr, " \
[%s(), %s:%u]\n" x, __FUNCTION__, __FILE__,__LINE__, ## args)
#else
#define DEBUGP(x, args ...)
#endif

#define swap(x,y) do \
    { unsigned char swap_temp[sizeof(x) == sizeof(y) ? (signed)sizeof(x) : -1]; \
	memcpy(swap_temp,&y,sizeof(x)); \
	memcpy(&y,&x,       sizeof(x)); \
	memcpy(&x,swap_temp,sizeof(x)); \
    } while(0)


typedef enum {FALSE, TRUE} EBool;

void array_swap(int A[], int m, int n);
void array_print(int array[], int length);

#endif /* _REQUIRE_H_ */
