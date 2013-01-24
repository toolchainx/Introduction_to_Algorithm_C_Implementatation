#ifndef _QUEUE_H_
#define _QUEUE_H_

#define QSIZE 20

typedef struct tag_queue
{
    int head;
    int tail;
    int array[QSIZE];
}Queue;

// 入队操作
int enqueue(Queue* q, int value);

// 出队操作
int dequeue(Queue* q, int* pvalue);

// 打印队列中的成员
void printQueue(Queue* q);
#endif /* _QUEUE_H_ */
