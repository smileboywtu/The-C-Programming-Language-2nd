#include"stdio.h"
#include"flag.h"

/**

	this program just test the get int function.

*/


int getfloat(float *p2i);



int main( void ){

	int index;
	float array[128];
	int flag;
	
	index = 0;
	while(index < 128){	
		// get float
		flag = getfloat(array+index);

		if(flag == EOF){
			break;
		}else if(flag == NUMBER){	
			// show the result
			printf("the data in array of index %d is %f.\n", index, array[index]);	
			index++;
		}else if(flag == INVALID){
			printf("ignore a character from the stream.\n");
		}

	}

	return 0;
}
