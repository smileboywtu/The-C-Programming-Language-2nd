#include "stdio.h"

/**
	this program convert fahr to celsius
*/

int main()
{

	int fahr, celsius;
	int lower, upper, step;

	int test, test2;

	lower = 0;
	upper = 300;
	step = 20;

	fahr = lower;
	printf("Fahr	5*deta/9	(5/9)*deta	(5.0/9.0)*deta\n");
	while(fahr <= upper)
	{
		// calclulate
		celsius = 5*(fahr - 32)/9;
		test = (5/9)*(fahr-32);
		test2 = (5.0/9.0)*(fahr-32);
		printf("%d\t%d\t\t%d\t\t%d\n", fahr, celsius, test, test2);
		// increase
		fahr += step;
	}	
	
	// notify the user
	printf("why the third colum is always zero?\n");
	printf("In C programming, Integer division truncate: any fractional part is discarded.\n");
		
	return 0;
}
