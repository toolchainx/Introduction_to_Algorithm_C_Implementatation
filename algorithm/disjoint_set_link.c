// 如何实现结点指向链表的指针？
// 有两种方式
// - 每个结点保存指向链表的指针
// - 每个链表的代表多一个指向链表的指针成员，将该成员指向链表，其他结点通过代表指向链表
// 第一种方式的缺点是浪费空间
// 第二种方式的缺点是实现较困难，要多态？
// 第二种实现方式有问题，目前采用第二种实现方式
// 实现不相交集合这一数据结构，须支持以下操作
// MAKE-SET(x) 建立一个新的集合
// DISJOINT_SET_UNION(x, y) 将包含x和y的集合合并为一个新的集合
// FIND-SET(x) 返回一个指针，指向包含x(唯一)集合的代表
#define NIL NULL

#include <stdio.h>
#include <stdlib.h>

typedef struct tagDjsLink *DjsLink;
typedef struct tagDjsNode
{
    int key;
    struct tagDjsNode* next;
    struct tagDjsNode* representative;
    // link指向链表结点
    DjsLink link;
    
}DjsNode, *DjsPNode;

typedef struct tagDjsLink{
    int length;
    DjsPNode head;
    DjsPNode tail;
}*DjsLink;

DjsPNode make_node(int k)
{
    DjsPNode x = (DjsPNode)malloc(sizeof(*x));
    x->key = k;
    x->next = NIL;
    x->representative = NIL;
    x->link = NIL;
    return x;
}
// MAKE-SET(x) 建立一个新的集合
// x为指向某一结点的指针
// 该结点为刚刚初始化的结点
DjsLink make_set(DjsPNode x)
{
    DjsLink link = (DjsLink)malloc(sizeof(*link));
    x->representative = x;
    x->link = link;
    link->head = x;
    link->tail = x;
    link->length = 1;
    return link;
}

// FIND-SET(x) 返回一个指针，指向包含x(唯一)集合的代表
DjsPNode find_set(DjsPNode x)
{
    return x->representative;
}
// DISJOINT_SET_UNION(x, y) 将包含x和y的集合合并为一个新的集合
// 更新代表指针
// 更新结点的链表指针
DjsLink disjoint_set_union(DjsPNode x, DjsPNode y)
{
    DjsPNode xRep = find_set(x);
    DjsPNode yRep = find_set(y);
    DjsPNode current;
    DjsLink xLink = xRep->link;
    DjsLink yLink = yRep->link;
    if (xRep == yRep)
    {
	return xLink;
    }
    // 比较两个链表的长度，将短的链表链接到长的链表的尾巴上
    if(xLink->length > yLink->length)
    {
	// 交换xLink和yLink的指针，使得xLink始终指向较短的链表
	DjsLink tmp = xLink;
	xLink = yLink;
	yLink = tmp;
    }
    // 将x链接到y链表后
    yLink->tail->next = xLink->head;
    yLink->tail = xLink->tail;
    yLink->length += xLink->length;
    // 更新x链表所有结点的代表指针，指向y集合的代表
    current = xLink->head;
    while (current) 
    {
	current->representative = yLink->head;
	current->link = yLink;
	current = current->next;
    }
    free(xLink);
    return yLink;
}

// 打印集合
void disjoint_set_print(DjsLink link)
{
    DjsPNode x = link->head;
    while (x != NIL) {
	printf("%d ", x->key);
	x = x->next;
    }
    printf("\n");
}

// test the disjoint_set
// find_set
// make_set
// disjoint_set_union
int main(int argc, char *argv[])
{
    const int size = 16;
    int i;
    DjsPNode x[size];
    DjsPNode rep1, rep2;
    for (i = 0; i < size; i++) {
	x[i] = make_node(i);
	make_set(x[i]);
    }
    for (i = 0; i < size-1; i = i + 2) {
	disjoint_set_union(x[i], x[i+1]);
	disjoint_set_print(x[i]->link);
    }
    for (i = 0; i < size-3; i = i + 4) {
	disjoint_set_union(x[i], x[i+2]);
	disjoint_set_print(x[i]->link);
    }
    disjoint_set_union(x[1], x[5]);
    disjoint_set_print(x[1]->link);
    disjoint_set_union(x[11], x[13]);
    disjoint_set_print(x[11]->link);
    disjoint_set_union(x[1], x[10]);
    disjoint_set_print(x[1]->link);
    rep1 = find_set(x[2]);
    printf("rep1 is: %d\n", rep1->key);
    rep2 = find_set(x[9]);
    printf("rep2 is: %d\n", rep2->key);
    return 0;
}

