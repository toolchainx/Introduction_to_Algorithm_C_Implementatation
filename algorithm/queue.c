// 实现先进先出队列的数据结构，以及出队，入队
// 队列的长度问题？
#include <stdio.h>
#include "queue.h"
// 队头和队尾的索引利用求余来进行卷绕
// 入队操作
int enqueue(queue* q, int value)
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
int dequeue(queue* q, int* pvalue)
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

void printQueue(queue* q)
{
    int i = q->head;
    while (i != q->tail) {
	printf("%d ",q->array[i]);
	i = (i + 1) % QSIZE;
    }
    printf("\n");
}
/* int main(int argc, char *argv[]) */
/* { */
/*     int array[] = {1, 2, 3, 4, 5, 6}; */
/*     int i; */
/*     queue q; */
/*     q.head = q.tail = 0; */
/*     for (i = 0; i < sizeof(array)/sizeof(array[0]); i++) { */
/* 	int value; */
/* 	printQueue(&q); */
/* 	dequeue(&q, &value); */
/*     } */
/*     for (i = 0; i < sizeof(array)/sizeof(array[0]); i++) { */
/*     	int value; */
/* 	enqueue(&q, array[i]); */
/*     	printQueue(&q); */
/*     } */
/*     return 0; */
/* } */
