#ifndef _ALL_PAIR_SHORTEST_PATH_H_
#define _ALL_PAIR_SHORTEST_PATH_H_
// 定义邻接矩阵的数据结构
// 包括元素rows:表示顶点的个数
// int**　mat 保存边的权值
#include <stdio.h>
#include "include/require.h"
#include "adj_mat.h"


// 假定l和w的顶点个数和矩阵的内容已设置好
// 数据结构多用指针来表示？
// 注意该函数有3个邻接矩阵同时参与运算
// l 和 w能否指向相同的内存？ 视情况而定
void extend_shortest_paths(const AdjMat* l, AdjMat* lquote, const AdjMat* w);
// 假定w已分配内存，设置了正确的值
AdjMat* slow_all_pair_shortest_path(const AdjMat* w);
AdjMat* faster_all_pair_shortest_path(const AdjMat* w);

#endif /* _ALL_PAIR_SHORTEST_PATH_H_ */
