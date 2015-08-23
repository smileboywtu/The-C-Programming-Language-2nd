#include "stdio.h"
#include "float.h"
#include "limits.h"

/**
	
	show the renge if the basic type.

*/

int main(){

	// char
	printf("show the char type: \n");
	printf("the size of char: %ld\n", sizeof(char));
	printf("the default min value of char: %d\n", CHAR_MIN);
	printf("the min value of signed char: %d, the max value of signed char: %d\n", SCHAR_MIN, SCHAR_MAX); 
	printf("the min value of unsigned char: %d, the max value of unsigned char: %d\n", CHAR_MIN, UCHAR_MAX); 
	printf("\n");

	// short
	printf("show the short type: \n");
	printf("the size of short: %ld\n", sizeof(short));
	printf("the min value of signed short: %d, the max value of signed short: %d\n", SHRT_MIN, SHRT_MAX);
	printf("the min value of unsiged short: %d, the max value of unsigned short: %u\n", 0, USHRT_MAX);
	printf("\n");

	// int
	printf("show the int type: \n");
	printf("the size of int: %ld\n", sizeof(int));
	printf("the min value of signed int: %d, the max value of signed int: %d\n", INT_MIN, INT_MAX);
	printf("the min value of unsiged int: %d, the max value of unsigned int: %u\n", 0, UINT_MAX);
	printf("\n");

	// long
	printf("show the long type: \n");
	printf("the size of long: %ld\n", sizeof(long));
	printf("the min value of signed long: %ld, the max value of signed long: %ld\n", LONG_MIN, LONG_MAX);
	printf("the min value of unsiged long: %d, the max value of unsigned long: %lu\n", 0, ULONG_MAX);
	printf("\n");

	// float
	printf("show the float type: \n");
	printf("the size of float: %ld\n", sizeof(float));
	printf("the min float value is: %.10e\n", FLT_MIN);
	printf("the max float value is: %.10e\n", FLT_MAX);
	printf("\n");

	// double
	printf("show the double type: \n");
	printf("the size of double: %ld\n", sizeof(double));
	printf("the min double value is: %.10e\n", DBL_MIN);
	printf("the max double value is: %.10e\n", DBL_MAX);	
	printf("\n");

	// long double
	printf("show the long double type: \n");
	printf("the size of long double: %ld\n", sizeof(long double));
	printf("the min long double value is: %Lg\n", LDBL_MIN);
	printf("the max long double value is: %Lg\n", LDBL_MAX);	
	printf("\n");

	return 0;
}
