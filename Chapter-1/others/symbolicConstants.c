#include "stdio.h"

/**
	this program using the symbolic constants to deal with the 'magic numbers' in C.

*/

#define UPPER	300
#define LOWER	0
#define STEP	10

int main(){

	int fahr;

	printf("Fahr	celsius\n");

	for(fahr=LOWER; fahr<=UPPER; fahr+=STEP){
		printf("%d\t%6.1f\n", fahr, (5.0/9)*(fahr-32));
	}
	
	return 0;
}
