#include "stdio.h"

/**

	this program convert the celsius temperature to the fahr.

*/

int main(){

	float celsius, fahr;
	int lower, upper, step;

	lower = -32;
	upper = 200;
	step = 15;

	celsius = lower;
	printf("Celsius	Fahr\n");
	while(celsius <= upper){
		fahr = 9.0*celsius/5.0+32;
		printf("%6.0f\t%4.1f\n", celsius, fahr);
		celsius += step;
	}
	return 0;
}
