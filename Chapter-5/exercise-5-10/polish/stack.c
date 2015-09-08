#include "ctype.h"

/**

	this is the stack we use to save the operands.

*/

#define STACK_SIZE	1024

static double stackBuffer[STACK_SIZE];
static int sp;

void push(double item){
	if(sp < STACK_SIZE-1){
		stackBuffer[sp++] = item;
	}
}

double pop(void){

	if(sp > 0){
			
		return stackBuffer[--sp];
	}

	return -1;
}
