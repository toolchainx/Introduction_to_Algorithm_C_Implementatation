#include "queue.h"

int main(int argc, char *argv[])
{
    int array[] = {1, 2, 3, 4, 5, 6};
    int i;
    Queue q;
    q.head = q.tail = 0;
    for (i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
	int value;
	printQueue(&q);
	dequeue(&q, &value);
    }
    for (i = 0; i < sizeof(array)/sizeof(array[0]); i++) {
    	int value;
	enqueue(&q, array[i]);
    	printQueue(&q);
    }
    return 0;
}
