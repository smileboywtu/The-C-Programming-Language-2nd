#include "ctype.h"
#include "assert.h"

/**
	
	static stack. 

*/

#define MAX_SIZE	100

int sp;
double stack[MAX_SIZE];

/* push */
void push(double item){
	
	// assert first
	assert(sp < MAX_SIZE);
	
	stack[sp++] = item;
}

/* pop */
double pop(void){
	
	// check first
	assert(sp > 0);

	return stack[--sp];
}

/* peek */
double peek(void){

	// check first
	assert(sp > 0);

	return stack[sp-1];
}

/* swap the top two. */
void swaptop2(void){

	// check first
	assert(sp >= 2);
	
	double a;

	a = stack[sp-1];
	stack[sp-1] = stack[sp-2];
	stack[sp-2] = a;
}

/* clear the stack. */
void clearstatck(void){
	
	sp = 0;

}
