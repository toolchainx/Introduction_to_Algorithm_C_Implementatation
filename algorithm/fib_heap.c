// 实现Fibnacci heap
// 可合并堆操作
// INSERT
// MINIMUM
// EXTRACT-MIN
// UNION
// 普通操作
// DECREASE-KEY
// DLETE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "fib_heap.h"

/* 利用一个函数实现根表的连接 */
// 假定root1是自完整的
// 假定root2是自完整的
void concatenate_root_list(RootTblPtr root1, RootTblPtr root2)
{
    /* 在root1的左边把环打开，同时在root2的右边把环打开 */
    /* 最后把这两个环对接上 */
    /* 考虑root1和root2均可能为NIL的情况 */
    /* 连接后返回root1 */
    RootTblPtr root1Left;
    RootTblPtr root2Right;
    if (root1 != NIL && root2 != NIL)
    {
	// 此时h1 和 h2 均不为NIL
	root1Left = root1->left;
    	root2Right = root2->right;
	root1->left = root2;
	root1Left->right = root2Right;
	root2->right = root1;
	root2Right->left = root1Left;
    }    
}


/* 创建一个新的Fibnacci 堆 */
FibHeap make_fib_heap()
{
    FibHeap h = (FibHeap)malloc(sizeof(*h));
    h->n = 0;
    h->min = NIL;
    return h;
}

/* 插入一个结点 */
int fib_heap_insert(FibHeap h, FbhPNode x)
{
    x->degree = 0;
    x->parent = NIL;
    x->child = NIL;
    x->left = x;
    x->right = x;
    x->mark = FALSE;
    /* concatenate the root list containing x with root list H */
    /* 在min的左边进行插入 */
    /* rootTbl可能为NULL */
    /* rootLeft可能为NIL */
    concatenate_root_list(h->min, x);
    if (h->min == NIL || x->key < h->min->key)
    {
	h->min = x;
    }
    h->n++;    
    return 0;
}

// 返回指向最小结点的指针
FbhPNode fib_heap_minimum(FibHeap h)
{
    return h->min;
}

// 合并两个Fibonacci 堆
FibHeap fib_heap_union(FibHeap h1, FibHeap h2)
{
    FibHeap h = make_fib_heap();
    h->min = h1->min;
    /* concatenate the root list of h2 with the root list of h */
    concatenate_root_list(h->min, h2->min);
    if (h1->min == NIL || (h2->min != NIL && h2->min->key < h1->min->key))
    {
	h->min = h2->min;
    }
    h->n = h1->n + h2->n;
    // free h1 and h2
    h1->min = NIL;
    h2->min = NIL;
    free(h1);
    free(h2);
    return h;
}

// 假定x和y均不为NIL，且x和y均为根表中的结点
// 将y作为x的子结点
// 修改y和x的变量名，y -> bechild x -> beparent
void fib_heap_link(FibHeap h, FbhPNode y, FbhPNode x)
{
    // remove y from the root list of h
    y->right->left = y->left;
    y->left->right = y->right;
    y->left = y;
    y->right = y;
    // make y a child of x, incrementing degree[x]
    concatenate_root_list(x->child, y);
    if(x->child == NIL)
    {
	x->child = y;
    }
    x->degree++;
    y->parent = x;
    y->mark = FALSE;
}

// 假定h不为NIL, 且h->min也不为NIL
// 此时最小关键字的结点已被抽取
void consolidate(FibHeap h)
{
    // 使用了一个辅助数组array[0.. D(n[h])] D(n[h])为结点的最大度数的已知上界
    // D(n[h]) <= floor(以(1 + sqrt(5))/2为底对n求对数)
    const int dupperbound = (int)(log(h->n)/log((1 + sqrt(5.0))/2.0))+1;
    FbhPNode array[dupperbound];
    FbhPNode w, x, y, sentinel;
    printf("the number of the heap node is %d\n", h->n);
    printf("the dupperbound is %d\n", dupperbound);
    int i,d;
    for (i = 0; i < dupperbound; i++) {
	array[i] = NIL;
    }
    // 根表是环形链表，如何测试环形链表的结尾？
    // 且环形链表发生了变化
    w = h->min;
    sentinel = w;
    do {
	x = w;
	w = w->right;
	d = x->degree;
	while (array[d] != NIL) {
	    // another node with the same degree as x
	    y = array[d];
	    // 始终将x作为父结点
	    if (x->key > y->key)
	    {
		// 交换x和y的指针
		// 如果x和哨兵sentinel指向同一个结点
		// 同时改变哨兵的指针
		FbhPNode tmp = x;
		x = y;
		y = tmp;
	    }
	    // 注意调整哨兵用来判断循环的结束！！！
	    if (sentinel == y) {
		// 若w在当前迭代的过程中已指向哨兵
		// 更改w，让其指向新的哨兵
		if (w == sentinel)
		{
		    w = x;
		}
		sentinel = x;
	    }
	    // 将y作为x的子结点
	    fib_heap_link(h, y, x);
	    array[d] = NIL;
	    d++;
	    // error here!
	    // to be continued...
	    printf("d is %d\n", d);
	    assert(d < dupperbound);
	}
	array[d] = x;
    }while (w != sentinel);
    h->min = NIL;
    // 确保插入前，树与树之间没有联系
    for (i = 0; i < dupperbound; i++) {
	if (array[i] != NIL)
	{
	    array[i]->right = array[i];
	    array[i]->left = array[i];
	}
    }

    for (i = 0; i < dupperbound; i++) {
	if (array[i] != NIL)
	{
	    // add array[i] to the root list of h
	    concatenate_root_list(h->min, array[i]);
	    if (h->min == NIL || array[i]->key < h->min->key)
	    {
		h->min = array[i];
	    }
	}
    }
}
// 抽取最小结点
RootTblPtr fib_heap_extract_min(FibHeap h)
{
    RootTblPtr z = h->min;
    RootTblPtr x;
    RootTblPtr xright;
    if (z != NIL)
    {
	// for each child x of z
	// do add x to the root list of h
	// p[x] = NIL
	x = z->child;
	// 如何设计这个循环不变式
	while (x != NIL) {
	    // 将x从z的子环形链表中提取出来
	    if (x != x->right) {
		xright = x->right;
	    }
	    else {
		xright = NIL;
	    }
	    x->left->right = x->right;
	    x->right->left = x->left;
	    x->right = x;
	    x->left = x;
	    x->parent = NIL;
	    // 将z的孩子加入到根表中
	    concatenate_root_list(h->min, x);
	    x = xright;
	}
	// remove z from the root list of h
	z->left->right = z->right;
	z->right->left = z->left;
	if (z == z->right)
	{
	    h->min = NIL;
	}
	else
	{
	    h->min = z->right;
	    // test here!!! h->n == 8
	    consolidate(h);
	}
	z->right = z;
	z->left = z;
	h->n--;
    }
    return z;
}


// 假定h->min不为NIL，x不为NIL，y不为NIL
void cut(FibHeap h, FbhPNode x, FbhPNode y)
{
    // remove x from the child list of y, decrementing degree[x]
    // 考虑x是y唯一的子结点？
    // x == y->child?
    if (x != x->right)
    {
	// x 不是y的唯一子结点
	y->child = x->right;
	x->right->left = x->left;
	x->left->right = x->right;
	x->right = x;
	x->left = x;
    }
    else
    {
	y->child = NIL;
    }
    y->degree--;
    // add x to the root list of h
    concatenate_root_list(h->min, x);
    // p[x] = NIL
    x->parent = NIL;
    // mark[x] = FALSE
    x->mark = FALSE;
}

void cascading_cut(FibHeap h, FbhPNode y)
{
    FbhPNode z = y->parent;
    if (z != NIL)
    {
	if (y->mark == FALSE)
	{
	    y->mark = TRUE;
	}
	else
	{
	    cut(h, y, z);
	    cascading_cut(h, z);
	}
    }
}

// 减小一个关键字
// 假定从链表中删除一个结点并不改变被删除结点的任何结构域
void fib_heap_decrease_key(FibHeap h, FbhPNode x, int k)
{
    FbhPNode y;
    if (k > x->key)
    {
	printf("new key is greater than the current key\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    x->key = k;
    y = x->parent;
    if (y != NIL && x->key < y->key)
    {
	// 把x从y的子结点中取出来，放到根结点中去
	cut(h, x, y);
	cascading_cut(h, y);
    }
    if (x->key < h->min->key)
    {
	h->min = x;
    }
}

void fib_heap_delete(FibHeap h, FbhPNode x)
{
    fib_heap_decrease_key(h, x, INT_MIN);
    fib_heap_extract_min(h);
}

FbhPNode fib_heap_node_allocate(int key)
{
    FbhPNode x = (FbhPNode)malloc(sizeof(FbhNode));
    x->key = key;
    x->inq = TRUE;
    return x;
}

FbhPNode testPtr;
FibHeap fib_heap_construct(int arr[], int length)
{
    int i;
    FibHeap h = make_fib_heap();
    FbhPNode x;
    assert(length >= 0);
    for (i = 0; i < length; i++) {
	x = fib_heap_node_allocate(arr[i]);
	if (arr[i] == 52)
	{
	    testPtr = x;
	}
	fib_heap_insert(h, x);
    }
    return h;    
}

// 打印所有的元素
void fib_heap_root_print(FbhPNode r)
{
    FbhPNode x = r;
    FbhPNode sentinel = x;
    if (x != NIL)
    {
	do 
	{
	    printf("%d \n", x->key);
	    if (x->child)
	    {
		printf("down\n");
		fib_heap_root_print(x->child);
		printf("up\n");
	    }
	    x = x->right;
	} while(x != sentinel);
    }
    fflush(stdout);
}
// test the Fibonacci heap
/* int main(int argc, char *argv[]) */
/* { */
/*     int arr1[NUMARRAY] = {23, 7, 21, 3}; */
/*     // int arr1[NUMARRAY] = {3, 7, 23, 21, 24, 18, 52, 17}; */
/*     int arr2[NUMARRAY] = {17, 24, 18, 52}; */
/*     // 构建堆 */
/*     FibHeap h1 = fib_heap_construct(arr1, sizeof(arr1)/sizeof(*arr1)); */
/*     printf("h1:\n"); */
/*     // fib_heap_extract_min(h1); */
/*     fib_heap_root_print(h1->min); */
/*     FibHeap h2 = fib_heap_construct(arr2, sizeof(arr2)/sizeof(*arr2)); */
/*     printf("h2:\n"); */
/*     fib_heap_root_print(h2->min); */
/*     FibHeap h = fib_heap_union(h1, h2); */
/*     printf("h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     RootTblPtr min = fib_heap_extract_min(h); */
/*     printf("min = %d\n", min->key); */
/*     fib_heap_root_print(h->min); */
/*     min = fib_heap_minimum(h); */
/*     fib_heap_decrease_key(h, min, 5); */
/*     printf("after decreased key h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     fib_heap_delete(h, min); */
/*     printf("after delete key h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     fib_heap_delete(h, testPtr); */
/*     printf("after delete key 52 h:\n"); */
/*     fib_heap_root_print(h->min); */
/*     return 0; */
/* } */
