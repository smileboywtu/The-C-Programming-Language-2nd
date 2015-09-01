#include "stdio.h"

/**

	this progarm just use to test the scope of the global variables.

*/

int sp;		// sp is the global variables.


void shadowornot(void){

	int sp;

	sp = 3;
	if(sp == 0){

		printf("local variable with same name do not shadow the external variable. \n");

	}else{

		printf("local variable will shadow the global variables.\n");

	}

}


int main(void){

	shadowornot();

	return 0;
}
