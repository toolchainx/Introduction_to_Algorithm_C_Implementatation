#ifndef _STACK_H_
#define _STACK_H_

#include "include/require.h"
#include "list.h"
typedef List Stack;

Stack make_stack();
void push(Stack s, int value);
EBool pop(Stack s, int* pv);
void print_stack(Stack s);

#endif /* _STACK_H_ */
