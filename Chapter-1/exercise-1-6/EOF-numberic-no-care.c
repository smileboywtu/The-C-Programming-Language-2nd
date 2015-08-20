#include "stdio.h"

/**

	EOF is numberic no care integer as long as it's not the same as any char value.
	But how to type invalid character from the keyboard?
*/

#define EOF_ 9090

int main(){

	int c;

	c = getchar();

	while(EOF != c){
		putchar(c);
		putchar(10);
		printf("show the value of c: %d\n", c);
		c = getchar();
	}

	return 0;
}
		
