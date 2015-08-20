#include "stdio.h"

/**
	use the float data type to save the result.

*/ 

int main(){

	float fahr, celsius;
	int lower, upper, step;

	lower = 0;
	upper = 300;
	step = 20;

	celsius = lower;
	printf("Celsius\tFhar\n");
	while(celsius <= upper){
		fahr = celsius*9.0/5.0+32;
		printf("%3.0f\t%4.2f\n", celsius, fahr);
		celsius += step;
	}
	return 0;
}
