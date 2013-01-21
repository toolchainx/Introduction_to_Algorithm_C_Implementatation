#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QSIZE 20

typedef struct tag_queue
{
    int head;
    int tail;
    int array[QSIZE];
}queue;

// 入队操作
int enqueue(queue* q, int value);

// 出队操作
int dequeue(queue* q, int* pvalue);

// 打印队列中的成员
void printQueue(queue* q);
#endif /* _QUEUE_H_ */
