#include "stdio.h"

/**

	self-increate operator and self-decrese operator.

*/

int main(){

	int i;
	
	int b;

	i = 0;
	b = 0;

	b += ((i++)+(++i)+(i++));

	printf("the value of i is: %d.\n", b);

	return 0;
}
