// 实现不相交集合这一数据结构，须支持以下操作
// MAKE-SET(x) 建立一个新的集合
// UNION(x, y) 将包含x和y
// FIND-SET(x) 返回一个指针，指向包含x(唯一)集合的代表
// 不相交集合森林的实现
// 通过引入两种启发式策略
// 按秩合并
// 路径压缩
// 问题： 只有父结点指针，没有子女结点的指针，如何遍历所有的结点？ 不需要遍历吗？
#include <stdio.h>
#include <stdlib.h>
#include "disjoint_set_forest.h"

// 创建一个结点
DjsTreeNodePtr djsforest_make_node(int k)
{
    DjsTreeNodePtr x = (DjsTreeNodePtr)malloc(sizeof(*x));
    x->key = k;
    x->parent = NIL;
    return x;
}

// 创建一个集合
DjsTree djsforest_make_set(DjsTreeNodePtr x)
{
    x->rank = 0;
    x->parent = x;
    return x;
}

// 寻找该结点所在集合的代表
DjsTreeNodePtr djsforest_find_set(DjsTreeNodePtr x)
{
    // 实现路径压缩的功能
    if (x != x->parent)
    {
	// 递归实现
	x->parent = djsforest_find_set(x->parent);
    }
    return x->parent;
}
// 链接两棵有根树
DjsTree djsforest_link(DjsTreeNodePtr rep1, DjsTreeNodePtr rep2)
{
    if (rep1->rank > rep2->rank )
    {
	rep2->parent = rep1;
	return rep1;
    }
    else
    {
	rep1->parent = rep2;
    }
    if (rep1->rank == rep2->rank)
    {
	rep2->rank++;
    }
    return rep2;
}

// 合并两个结点所在地集合
DjsTree djsforest_union(DjsTreeNodePtr x, DjsTreeNodePtr y)
{
    return djsforest_link(djsforest_find_set(x), djsforest_find_set(y));
}



/* int main(int argc, char *argv[]) */
/* { */
    
/*     return 0; */
/* } */
