#include "func.h"
#include "stdio.h"
#include "ctype.h"
#include "stdlib.h"

/**

	this program will calculate the polish expression.

*/


int main(int argc, char* argv[]){

	int indexofargv;
	int type;
	double operand;

	if(argc == 1){
		printf("Usage: expr pilish-expression\n");
		return -1;
	}

	for(indexofargv=1; indexofargv < argc; indexofargv++){

		type = gettype(*(argv+indexofargv));
		switch(type){
			case NUMBER:
				{ push(atof(*(argv+indexofargv))); break;}
			case '+':
				{ operand = pop(); push(pop() + operand); break;}
			case '-':
				{ operand = pop(); push(pop() - operand); break;}
			case '*':
				{ operand = pop(); push(pop() * operand); break;}
			case '/':
				{ operand = pop(); if(operand != 0){ push(pop() / operand);}else{ 	printf("illegal divider.\n");} break;}
			default:
				{ printf("illegal element.\n"); break;}	
		}	
	}

	printf("%lf\n", pop());
		
	return 0;
}

