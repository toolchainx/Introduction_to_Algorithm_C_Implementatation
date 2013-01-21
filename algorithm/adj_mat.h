#ifndef _ADJ_MAT_H_
#define _ADJ_MAT_H_
#include "include/require.h"

typedef struct tagAdjMat
{
    int rows;
    int** mat;
}AdjMat;



// 构建邻接矩阵
// make 分配内存，赋值为INFINITE
// construct 分配内存，同时赋值 

// 创建邻接矩阵，顶点的个数为numVertices
AdjMat* make_adjmat(int numVertices);
AdjMat* make_param_adjmat(int numVertices, int pdv, int npdv);
// 获取文件内容的方式：
// 先获得顶点的个数
// 然后再获得两个顶点及其边的权重
// 获得文件名？ 还是获得文件结构的指针？
// 根据解耦的原则不应该要求该函数对文件打开操作负责
AdjMat* construct_adjmat(FILE* pFile);
AdjMat* construct_param_adjmat(FILE* pFile, int pdv, int npdv);
AdjMat* copy_adjmat(const AdjMat* m);
void free_adjmat(AdjMat* m);
// |1   2   -3  |
// |INF INF -9  |   
void print_adjmat(const AdjMat* m);

#endif /* _ADJ_MAT_H_ */
