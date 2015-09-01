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
