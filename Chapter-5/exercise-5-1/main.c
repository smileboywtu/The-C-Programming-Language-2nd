#include"stdio.h"

/**

	this program just test the get int function.

*/


int getint(int *p2i);



int main( void ){

	int index;
	int array[128];
	
	for(index=0; index < 128 && getint(array+index) != EOF; index++){
		
		// show the result
		printf("the data in array of index %d is %d.\n", index, array[index]);	
	}

	return 0;
}
