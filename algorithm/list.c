// 实现一个链表的插入，删除，查找，

#include "list.h"
#include <stdio.h>
#include <stdlib.h>

// insert to the first of the list
List list_insert(List list, int value)
{
    PNode pNode = (PNode)malloc(sizeof(Node));
    pNode->value = value;
    pNode->next = list;
    list = pNode;
    return list;
}
void free_list(List list)
{
    PNode pNode = list;
    while (list) {
	list = list->next;
	free(pNode);
	pNode = list;
    }
    
}


void print_list(List list)
{
    while (list)
    {
	printf("%d ", list->value);
	list = list->next;
    }
    printf("\n");
}
