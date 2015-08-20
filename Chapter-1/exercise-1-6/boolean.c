#include "stdio.h"

/**

	this program test the boolean value of getchar != EOF return.

*/

int main(){

	short c;

	while(EOF != (c = getchar())){
		if('\n' == c){
			continue;
		}
		printf("the current character is: %c, the test is: true.\n", c);

	}

	printf("the current character is: EOF, the test is: false.\n");

	return 0;

}
