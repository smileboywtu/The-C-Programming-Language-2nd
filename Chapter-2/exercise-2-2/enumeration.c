#include "stdio.h"

/**
	
	the compiler need not to check the enumeration.

*/
enum Ball{vally, baseball, pingpang};
typedef enum Ball Ball;
typedef enum{Monday=1, Tuesday, Wesdnesday, Thursday, Friday, Saturday, Sunday} weekday;
typedef enum{RED=1, BLUE=2, GREEN=1} color;

int main(){

	weekday i = Thursday;
	color c = RED;
	Ball b = baseball;

	printf("%d\n", i);	
	if(c == RED){
		printf("RED\n");
	}
	if(c == GREEN){
		printf("GREEN\n");
	}

	printf("the ball is %d\n", b);

	return 0;
}
