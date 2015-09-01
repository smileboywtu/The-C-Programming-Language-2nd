#include "math.h"
#include "stdio.h"
#include "assert.h"
#include "stdlib.h"

/**

	calculate the polish.

*/

#define NUMBER 		1
#define MAX_POLISH_SIZE	1024

int gettop(char* str);
void push(double item);
double pop(void);
void swaptop2(void);
double peek(void);
int mod(double a, double b);

int main( void ){

	int type;
	double operand;
	char expression[MAX_POLISH_SIZE];

	while((type=gettop(expression)) != EOF){
		switch(type){
			case NUMBER:
				{	push(atof(expression)); break;}
			case '+':
				{ push(pop() + pop());	break;}
			case '*':
				{ push(pop() * pop()); 	break;}	
			case '-':
				{ swaptop2(); push(pop() - pop());	break;}
			case '/':
				{ operand = peek(); swaptop2(); assert(operand !=  0); push(pop() / pop()); break;}
			case '%':
				{ operand = peek(); swaptop2(); assert(operand !=  0); push(mod(pop(), operand)); break;}
			case '\n':
				{	printf("\t%.8g\n", pop()); break;}
			default:
				{ printf("error happens.\n"); break;}
		}

	}

	return 0;
}


/* calculate the mod. */
int mod(double a, double b){

	assert((int)a -	a == 0.0);
	assert((int)b - b == 0.0);

	int c = (int)a;
	int d = (int)b;

	if(c*d < 0){
		return -1*abs(abs(c)%abs(d)); 
	}else if(c*d > 0){
		if(d < 0){
			return -1*abs((-c)%(-d));
		}
		return abs(c%d);
	}

	return 0;
}
