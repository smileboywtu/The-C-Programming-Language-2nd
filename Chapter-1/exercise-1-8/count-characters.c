#include "stdio.h"

/**

	this program use to count the input characters.
*/

int main(){

	int counter;

	counter = 0;
	while(EOF != getchar()){
		++counter;
	}

	printf("You have input %d characters.\n", counter);

	return 0;
}
