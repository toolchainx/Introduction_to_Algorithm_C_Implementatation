#ifndef _MIN_PRIORITY_QUEUE_H_
#define _MIN_PRIORITY_QUEUE_H_
#include "include/require.h"

// max size of qNode* A[]
#define MAX_SIZE  20
typedef struct qNode_tag
{
    char c; // 标识元素
    int key; // 用于比较的关键字
}qNode;
qNode* create_node(char c, int key);
void min_queue_insert(qNode* A[], int* plength, qNode* x);
void queue_decrease_key(qNode* A[], int i, int key);
qNode* queue_extract_min(qNode* A[], int* plength);
qNode* queue_minimum(qNode* A[]);
void min_queue_output(qNode* A[], int length);
#endif /* _MIN_PRIORITY_QUEUE_H_ */
