#include "stdio.h"

/**

	shrink the program: copying input to output.

*/

int main(){

	int c;
	// keep care of using the parentheses
	// beacause the precedence of != is higher than that of =
	while(EOF != (c = getchar())){
		putchar(c);
	}

	return 0;
} 
