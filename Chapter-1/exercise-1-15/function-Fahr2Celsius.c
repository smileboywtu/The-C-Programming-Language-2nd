#include "stdio.h"

/**

	A batter way converting fahr to celsius.

*/


#define LOWER	0
#define UPPER	300
#define STEP	20

float fahr2cel(float);

int main(){
	
	float fahr, celsius;

	printf("Fahr	Celsius\n");
	for(fahr=LOWER; fahr <= UPPER; fahr += STEP){
		celsius =	fahr2cel(fahr);
		printf("%4.0f\t%6.1f\n", fahr, celsius);
	}

	return 0;

}


/*	convert the fahr to celsius  */
float fahr2cel(float fahr){
	return 5.0/9*(fahr-32);
}
