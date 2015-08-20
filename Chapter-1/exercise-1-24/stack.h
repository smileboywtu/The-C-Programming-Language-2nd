#ifndef __STACK__C__
#define __STACK__C_

/*****************************
		extern variables
*****************************/

typedef long ElemType;

struct StackNode{
	ElemType data;
	struct StackNode* pNext;
};

struct Stack{
	int size;
	struct StackNode* top;
};

/* you must define the struct here. */
typedef struct StackNode StackNode;
typedef struct Stack 		 Stack;


/*****************************
		extern funcs
*****************************/
void push(Stack* s, ElemType e);
ElemType pop(Stack* s);
ElemType peek(Stack* s);
int getsize(Stack* s);
void initstack(Stack* s);

#endif
