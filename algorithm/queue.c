// 实现先进先出队列的数据结构，以及出队，入队
// 队列的长度问题？
#include <stdio.h>
#include "queue.h"
// 队头和队尾的索引利用求余来进行卷绕
// 入队操作
int enqueue(Queue* q, int value)
{
    // q->tail 总是指向无元素的位置
    // q->head 总是指向队头元素
    if ((q->tail + 1) % QSIZE == q->head)
    {
	printf("the queue is full\n");
	printf("q.tail is %d\n", q->tail);
	printf("q.head is %d\n", q->head);
	return 0;
    }    
    q->array[q->tail] = value;
    q->tail = (q->tail + 1) % QSIZE;
    return 1;
}

// 出队操作
int dequeue(Queue* q, int* pvalue)
{
    // 判断队列是否为空
    if (q->head == q->tail)
    {
	printf("the queue is empty\n");
	return 0;
    }
    *pvalue = q->array[q->head];
    q->head = (q->head + 1)%QSIZE;
    return 1;
}

void printQueue(Queue* q)
{
    int i = q->head;
    while (i != q->tail) {
	printf("%d ",q->array[i]);
	i = (i + 1) % QSIZE;
    }
    printf("\n");
}
