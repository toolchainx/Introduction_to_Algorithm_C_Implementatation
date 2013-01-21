// 链表实现
// 实现栈的数据结构
#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

Stack make_stack()
{
    Stack stack = (Stack)malloc(sizeof(*stack));
    stack->next = NULL;
    return (Stack)stack;
}

void push(Stack s, int value)
{
    PNode pn = (PNode)malloc(sizeof(*pn));
    pn->value = value;
    pn->next = s->next;
    s->next = pn;
}

EBool pop(Stack s, int* pv)
{
    
    if (s->next != NULL)
    {
	List x = s->next;
	*pv = x->value;
	s->next = s->next->next;
	free(x);
	return TRUE;
    }
    else
    {
	return FALSE;
    }
}
void print_stack(Stack s)
{
    print_list(s->next);
}
