#include"stdio.h"

/**
	this program test the machine depend primery types in C programming.

*/

int main()
{

	char c  = 'c';
	short b = 20;
	int  i = 125;
	long l = 56L;
	float f = 0.2F;
	double d = 7.8F;

	// show the size
	printf("the size of char is: %ld\n", sizeof(c));
	printf("the size of short is: %ld\n", sizeof(b));
	printf("the size of int is: %ld\n", sizeof(i));
	printf("the size of long is: %ld\n", sizeof(l));
	printf("the size of float is: %ld\n", sizeof(f));
	printf("the size of double is: %ld\n", sizeof(d));

	// default return
	return 0;
}
