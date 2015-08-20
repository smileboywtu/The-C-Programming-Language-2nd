#include "stdio.h"

/**
	this interface it provide by the C Standard Library.
	this program show that copying the input to the output"
*/

int main(){

	int c;

	c = getchar();

	while(EOF != c){
		putchar(c);
		c = getchar();
	}
	
	// notify the user
	printf("int c; \nc = getchar();\n");
	printf("Here you may want to know why the auther use the integer not a character data type?\n");
	
	return 0;

}
