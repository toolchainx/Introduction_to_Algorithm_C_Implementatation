#ifndef _HUFFMAN_CODING_H_
#define _HUFFMAN_CODING_H_
// 使用最小优先级队列
#include "min_priority_queue.h"

typedef struct qInNode_tag
{
    qNode qn;
    qNode* left;
    qNode* right;
}qInNode;

typedef struct dict_tag
{
    char c;
    char* str;
}dict;

void freedict(dict* dt, int length);
void dict_output(dict* dt, int length);
void traverse(qNode* bt, dict* dt, char* str);
dict* huffman_genDict(qNode* bt, int numLeaf);
qNode* huffman(qNode* A[], int length);
void btree_output(qNode* bt);
#endif /* _HUFFMAN_CODING_H_ */
