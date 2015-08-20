#include "stdio.h"
#include "stack.h"

/**

	test the stack.

*/

int main(){

	Stack s;
	ElemType c, e;

	initstack(&s);

	printf("the init size is: %d\n", s.size);
	
	// push
	e = 'c';
	push(&s, e);
	printf("the stack size is: %d\n", s.size);
	putchar(peek(&s));
	putchar('\n');
	printf("the stack size is: %d\n", s.size);
	pop(&s);
	printf("the stack size is: %d\n", s.size);
	
	c = '1';
	push(&s, c);
	c = '2';
	push(&s, c);
	c = '3';
	push(&s, c);

	while(getsize(&s) > 0){
		putchar(pop(&s));
		putchar('\n');
	}

	return 0;
}

	 	
