#include "stdio.h"

/**

	swap the two argument of type t.

*/


#define swap(t, a, b) \
	{										\
		t tempvalue;			\
		tempvalue = b;		\
		b = a;						\
		a = tempvalue;		\
	}						


int main( void ){


	int a, b;

	a = 5;
	b = 3;

	printf("a = %d, b = %d.\n", a, b);

	swap(int, a, b);

	printf("a = %d, b = %d.\n", a, b);


	return 0;
}
	
