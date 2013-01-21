// 实现二项堆这一抽象数据结构
// 二项堆包含多课二项树
#include <stdio.h>
#include <stdlib.h>


#define NIL NULL
// 定义二项堆的数据结构
typedef struct tagBinomialHeap
{
    struct tagBinomialHeap* parent;
    struct tagBinomialHeap* child;
    struct tagBinomialHeap* sibling;
    int key;
    int degree;
}*BmHeap, *BmPNode, BmNode;


// 创建一个新的二项堆
BmHeap make_binomial_heap()
{
    return NIL;
}

// 寻找最小关键字
BmPNode binomial_heap_minimum(BmHeap h)
{
    // y 为要返回的最小关键字的指针
    // x 为迭代器
    // min 用于比较的临时变量
    BmPNode y = NIL;
    BmPNode x = h;
    int min = INT_MAX;
    while (x != NIL) {
	if (min > x->key)
	{
	    min = x->key;
	    y = x;
	}
	x = x->sibling;
    }
    return y;
}

// 连接二项树y和z，y和z的度数相同为degree,
// 连接后成为一颗度数为degree + 1的二项树
void binomial_link(BmHeap y, BmHeap z)
{
    y->parent = z;
    y->sibling = z->child;
    z->child = y;
    z->degree++;
}
void binomial_heap_print_tree(BmPNode t);
void binomial_heap_print_root(BmHeap h);
// 将二项堆h1和h2的根表合成一个根表h
// 返回一个按单调递增度数排序的根表h
BmHeap binomial_heap_merge(BmHeap h1, BmHeap h2)
{
    // 将h2插入到h1中
    // 寻找循环不变式
    // h1 始终是按单调递增顺序排列，但相邻结点间的度数可能相同
    // h2 始终是按单调递增的顺序排列，没有度数相同的结点
    // a2 在每次循环的开始，始终指向h2所指向的结点。
    // prev_a1始终指向a1的前一个结点，或为NIL
    // 分情况进行讨论
    // 根表h1最后一个结点的sibling成员不为NIL
    BmPNode prev_a1 = NIL;
    BmPNode a1 = h1;
    BmPNode a2 = h2;
    while (a2) {
	if (a1 == NIL)
	{
	    prev_a1->sibling = a2;
	    // 令循环结束
	    a2 = NIL;
	}
	else if (a2->degree > a1->degree)
	{
	    prev_a1 = a1;
	    a1 = a1->sibling;
	}
	else // a2 <= a1
	{
	    h2 = a2->sibling;
	    // 在a1的前面插入a2
	    if (prev_a1 == NIL)
	    {
		a2->sibling = h1;
		h1 = a2;
	    }
	    else
	    {
		a2->sibling = prev_a1->sibling;
		prev_a1->sibling = a2;
	    }
		prev_a1 = a2;
		a2 = h2;
	}
    }  
//    binomial_heap_print_root(h1);
    return h1;
}
// 合并两个二项堆
BmHeap binomial_heap_union(BmHeap h1, BmHeap h2)
{
    // 要返回的局部变量h
    BmHeap h;
    BmPNode prev_x;
    BmPNode x;
    BmPNode next_x;    
    // 该函数没有参数
    h = make_binomial_heap();
    h = binomial_heap_merge(h1, h2);
    h1 = NIL;
    h2 = NIL;
    if (h == NIL)
    {
	return h;
    }
    prev_x = NIL;
    x = h;
    next_x = x->sibling;
    while (next_x != NIL) {
	if (x->degree != next_x->degree ||  // case 1 and case 2
	    (next_x->sibling != NIL && next_x->sibling->degree == x->degree))
	{
	    prev_x = x;
	    x = next_x;
	}
	else if(x->key <= next_x->key)  // case 3
	{
	    x->sibling = next_x->sibling;
	    // 以x为根结点，连接next_x 和 x这两颗二项树
	    binomial_link(next_x, x);
	}
	else                           // case 4
	{
	    if(prev_x == NIL)
	    {
		h = next_x;
	    }
	    else
	    {
		prev_x->sibling = next_x;
	    }
	    binomial_link(x, next_x);
	    x = next_x;
	}
	next_x = x->sibling;
    }
    return h;
}

// 插入一个结点，假定x已分配内存，且key字段已赋值
BmHeap binomial_heap_insert(BmHeap* ph, BmPNode x)
{
    BmHeap hq = make_binomial_heap();    
    // 初始化x
    x->sibling = NIL;
    x->parent = NIL;
    x->child = NIL;
    x->degree = 0;
    hq = x;
    *ph = binomial_heap_union(hq, *ph);
    return *ph;
}
// 获取minimum 结点的前一个结点的指针
BmPNode binomial_heap_prev_min(BmHeap h)
{
    // find the root x with the minimum key in the root list of h,
    // and remove x from the root list of h
    BmPNode prev_x = NIL;
    BmPNode x = h;
    BmPNode prev_y = NIL;
    // 另一个解法，只利用prev_x 和 prev_y 来进行处理？
    int min = INT_MAX;
    while (x != NIL) {
	if (min > x->key)
	{
	    min = x->key;
	    prev_y = prev_x;
	}
	prev_x = x;
	x = x->sibling;
    }
    return prev_y;
}
// reverse the order of the linked list of x's children, setting 
// the parent field of each child to NIL,
// and set hq to point to the head of the resulting list
BmHeap binomial_heap_reverse_child(BmPNode y)
{
    // 将y的子女排序反转
    BmHeap h = make_binomial_heap();
    BmPNode x;
    BmPNode iter_x;
    x = y->child;
    y->child = NIL;
    while(x != NIL)
    {
	iter_x = x->sibling;
	// 将x插入到h所指向的二项堆的前端
	x->sibling = h;
	h = x;
	x = iter_x;
    }
    /* printf("reverse child\n"); */
    /* iter_x = h; */
    /* while(iter_x != NIL) */
    /* { */
    /* 	printf("key: %d, degree: %d\n", iter_x->key, iter_x->degree); */
    /* 	iter_x = iter_x->sibling; */
    /* } */
    /* printf("reverse childe end\n"); */
    return h;
}


// 抽取具有最小关键字的结点，并返回指向该结点的指针
// need to debug
BmPNode binomial_heap_extract_min(BmHeap* ph)
{
    // 如果prev_y 为NIL？
    BmHeap prev_y = binomial_heap_prev_min(*ph);
    printf("prev_y = %p\n", prev_y);
    BmHeap y;
    BmHeap hq = make_binomial_heap();
    // y is the minimum node and the prev_y is the node adjacent to y
    // in case that prev_y is NIL
    if (prev_y == NIL)
    {
	y = *ph;
	*ph = y->sibling;
    }
    else
    {
	y = prev_y->sibling;
	prev_y->sibling = y->sibling;
    }
    y->sibling = NIL;
    // reverse the order of the linked list of x's children, setting 
    // the parent field of each child to NIL,
    // and set hq to point to the head of the resulting list
    hq = binomial_heap_reverse_child(y);
    // error here!
    *ph = binomial_heap_union(hq, *ph);
    return y;
}

// 交换两个结点的关键字
void binomial_heap_key_swap(BmPNode lhs, BmPNode rhs)
{
    // if lhs and rhs have satellite fields, exchange them too.
    int tmp = lhs->key;
    lhs->key = rhs->key;
    rhs->key = tmp;
}
// 减小关键字的值
void binomial_heap_decrease_key(BmHeap h, BmPNode x, int k)
{
    BmPNode y;
    BmPNode z;
    if (k > x->key )
    {
	printf("new key is greater than current key\n");
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    x->key = k;
    y = x;
    z = y->parent;
    // 如果y的关键字比z的关键字小，冒泡上升
    // z 可能为NIL？
    while (z != NIL && y->key < z->key)
    {
	binomial_heap_key_swap(y, z);
	y = z;
	z = y->parent;
    }
}

// delete a node
void binomial_heap_delete(BmHeap* ph, BmPNode x)
{
    binomial_heap_decrease_key(*ph, x, INT_MIN);
    printf("derease_key completed\n");
    binomial_heap_extract_min(ph);
    free(x);
}

// 从文件中读入数据，构造二项堆
BmHeap construct_binomial_heap(const char* filename)
{
    FILE* pFile;
    BmHeap h = NIL;
    BmPNode x;
    int k;
    if ((pFile = fopen(filename, "r")) == NULL)
    {
	printf("can't open file %s\n", filename);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    while (!feof(pFile)) {
	fscanf(pFile, "%d", &k);
	x = (BmPNode)malloc(sizeof(BmNode));
	if (x == NULL)
	{
	    printf("can't malloc for var x, %s, %d\n", __FILE__, __LINE__);
	    fflush(stdout);
	    exit(EXIT_FAILURE);
	}
	x->key = k;
	binomial_heap_insert(&h, x);
	x = NULL;
    }
    fclose(pFile);
    printf("construct complete!\n");
    return h;
}
void binomial_heap_print_tree(BmPNode t)
{
    // 递归打印结点
    BmPNode x = t->child;
    printf("key: %d, degree: %d\n", t->key, t->degree);
    while (x) {
    	binomial_heap_print_tree(x);
    	x = x->sibling;
    }
    
}
void binomial_heap_print_root(BmHeap h)
{
    // 打印根表的关键字值和度数
    BmPNode x = h;
    char * test = "明天是更好的一天";
    while (x) {
	binomial_heap_print_tree(x);
	x = x->sibling;
    }
    printf("%s", test);
}
// 释放二项堆
void binomial_heap_free(BmHeap h)
{
    
}

// 如何测试二项堆？
// 测试每一个函数，测试每个函数的每一条路径
// 测试边界条件
// 如何设计一个良好的测试用例。
// 数据结构测试的方法
// 采用特殊的数据用例，调用以下函数
// make_heap()
// insert(h, x)
// minimum(h)
// extract_min(h)
// union(h1, h2)
// 以上操作为可合并堆(mergeable heap)支持的操作
// 二项堆和Fibonacci堆还支持下面两种操作
// decrease_key(h, x, k):将新关键字值k(假定它不大于当前的关键字值)赋给堆h中的结点x
// delete(h, x)
// 先测试核心函数UNION
int main(int argc, char *argv[])
{
    BmHeap h = make_binomial_heap();
    BmHeap h1 = make_binomial_heap();
    BmHeap h2 = make_binomial_heap();
    BmPNode min;
    if (argc < 2)
    {
	printf("%s filename.dat ... \n", argv[0]);
	fflush(stdout);
	exit(EXIT_FAILURE);
    }
    // 从文件中读入关键字值，插入结点，构造两个二项堆
    h1 = construct_binomial_heap(argv[1]);
    binomial_heap_print_root(h1);
    h2 = construct_binomial_heap(argv[2]);
    // binomial_heap_print_root(h2);
    // h = binomial_heap_union(h1, h2);
    printf("the result of union\n");
    binomial_heap_print_root(h);
    min = binomial_heap_minimum(h1);
    printf("the minimum number is %d\n", min->key);
    fflush(stdout);
    // extract_min有问题
    min = binomial_heap_extract_min(&h1);
    binomial_heap_print_root(h1);
    min = binomial_heap_minimum(h1);
    printf("the minimum number is %d\n", min->key);
    fflush(stdout);
    binomial_heap_delete(&h1, min);
    min = NIL;
    binomial_heap_print_root(h1);
    binomial_heap_free(h);
    return 0;
}
