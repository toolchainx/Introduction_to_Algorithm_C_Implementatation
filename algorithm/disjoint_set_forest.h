#ifndef _DISJOINT_SET_FOREST_H_
#define _DISJOINT_SET_FOREST_H_

#define NIL NULL

typedef struct tagTreeNode
{
    struct tagTreeNode* parent;
    int key;
    // rank is the height of the node
    int rank;
}DjsTreeNode, *DjsTree, *DjsTreeNodePtr;

// 创建一个结点
DjsTreeNodePtr djsforest_make_node(int k);
// 创建一个结点
DjsTreeNodePtr djsforest_make_node(int k);
// 创建一个集合
DjsTree djsforest_make_set(DjsTreeNodePtr x);
// 寻找该结点所在集合的代表
DjsTreeNodePtr djsforest_find_set(DjsTreeNodePtr x);
// 链接两棵有根树
DjsTree djsforest_link(DjsTreeNodePtr rep1, DjsTreeNodePtr rep2);
// 合并两个结点所在地集合
DjsTree djsforest_union(DjsTreeNodePtr x, DjsTreeNodePtr y);

#endif /* _DISJOINT_SET_FOREST_H_ */

