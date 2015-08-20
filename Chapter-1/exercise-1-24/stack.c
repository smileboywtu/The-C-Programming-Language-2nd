#include "stack.h"
#include "assert.h"
#include "stdlib.h"
/**
	implement of the stack in c.

*/

/*	init the stack. */
void initstack(Stack* s){

	s->size = 0;
	
	s->top = NULL;
}

/*	get the size */
int getsize(Stack* s){

	return s->size;
}

/* push data. */
void push(Stack* s, ElemType e){

	/* reset the node. */
	StackNode* newnode = (StackNode*)malloc(sizeof(StackNode));
	newnode->data = e;
	newnode->pNext = s->top;
	/* redirect to the new node. */
	s->top = newnode;

	s->size++;
}

/* pop the data. */
ElemType pop(Stack* s){

	assert(s->size > 0);

	StackNode* cur;
	ElemType e;

	cur = s->top;
	e = cur->data;

	s->size--;
	s->top = cur->pNext;
	free((StackNode*)cur);

	return e;
}

/* peek the top */
ElemType peek(Stack* s){

	assert(s->size > 0);

	ElemType e;

	e = s->top->data;

	return e;
}
