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

	fahr = lower;
	printf("Fahr\tCelsius\n");
	while(fahr <= upper){
		celsius = (5.0/9)*(fahr-32);
		printf("%3.0f\t%4.2f\n", fahr, celsius);
		fahr += step;
	}
	return 0;
}
