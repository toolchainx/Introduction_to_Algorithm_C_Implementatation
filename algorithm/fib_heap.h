#ifndef _FIB_HEAP_H_
#define _FIB_HEAP_H_

#include "include/require.h"
#define NUMARRAY 4
#define NIL NULL


typedef EBool Mark;
typedef struct tagRootTbl
{
    struct tagRootTbl* parent;
    struct tagRootTbl* child;
    struct tagRootTbl* left;
    struct tagRootTbl* right;
    int ref;
    Mark inq;
    int degree;
    int key;
    Mark mark;    
}*RootTblPtr, *FbhPNode, FbhNode;
typedef struct tagFibHeap
{
    int n;
    RootTblPtr min;
} *FibHeap;


/* 利用一个函数实现根表的连接 */
// 假定root1是自完整的
// 假定root2是自完整的
void concatenate_root_list(RootTblPtr root1, RootTblPtr root2);

/* 创建一个新的Fibnacci 堆 */
FibHeap make_fib_heap();

/* 插入一个结点 */
int fib_heap_insert(FibHeap h, FbhPNode x);

// 返回指向最小结点的指针
FbhPNode fib_heap_minimum(FibHeap h);

// 合并两个Fibonacci 堆
FibHeap fib_heap_union(FibHeap h1, FibHeap h2);

// 假定x和y均不为NIL，且x和y均为根表中的结点
// 将y作为x的子结点
// 修改y和x的变量名，y -> bechild x -> beparent
void fib_heap_link(FibHeap h, FbhPNode y, FbhPNode x);

// 假定h不为NIL, 且h->min也不为NIL
void consolidate(FibHeap h);

// 抽取最小结点
RootTblPtr fib_heap_extract_min(FibHeap h);

// 假定h->min不为NIL，x不为NIL，y不为NIL
void cut(FibHeap h, FbhPNode x, FbhPNode y);

void cascading_cut(FibHeap h, FbhPNode y);

// 减小一个关键字
// 假定从链表中删除一个结点并不改变被删除结点的任何结构域
void fib_heap_decrease_key(FibHeap h, FbhPNode x, int k);

void fib_heap_delete(FibHeap h, FbhPNode x);

FbhPNode fib_heap_node_allocate(int key);

FibHeap fib_heap_construct(int arr[], int length);

// 打印所有的元素
void fib_heap_root_print(FbhPNode r);



#endif /* _FIB_HEAP_H_ */
