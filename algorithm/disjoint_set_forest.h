#ifndef _DISJOINT_SET_FOREST_H_
#define _DISJOINT_SET_FOREST_H_

#define NIL NULL

typedef struct tagTreeNode
{
    struct tagTreeNode* parent;
    int key;
    // rank is the height of the node
    int rank;
}TreeNode, *Tree, *TreePNode;

// 创建一个结点
TreePNode djsforest_make_node(int k);
// 创建一个结点
TreePNode djsforest_make_node(int k);
// 创建一个集合
Tree djsforest_make_set(TreePNode x);
// 寻找该结点所在集合的代表
TreePNode djsforest_find_set(TreePNode x);
// 链接两棵有根树
Tree djsforest_link(TreePNode rep1, TreePNode rep2);
// 合并两个结点所在地集合
Tree djsforest_union(TreePNode x, TreePNode y);

#endif /* _DISJOINT_SET_FOREST_H_ */

