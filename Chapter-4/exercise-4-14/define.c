#include "stdio.h"


/**

	test the define with # and ##.

*/


#define DEF0(p)	printf(#p " is %d.\n", p)
#define DEF1(p, q) (p ## q)	


int main(void){

	int time;

	DEF0(2-3);
	printf("smile "  ", are you ok?\n");
	
	time = DEF1(12, 3);

	printf("the time is %d.\n", time);
	

	return 0;
}
