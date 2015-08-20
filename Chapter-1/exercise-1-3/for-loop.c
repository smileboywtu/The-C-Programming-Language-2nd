#include "stdio.h"

/**

	use the for loop to convert the temperature

*/

int main(){
	
	int fahr;

	printf("Fahr	Celsius\n");
	for(fahr=0; fahr<=300; fahr+=20){
		printf("%d\t%6.1f\n", fahr, 5.0*(fahr-32)/9.0);
	}
	
	return 0;
}
