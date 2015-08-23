#include "stdio.h"

/**

	count the 1-bit in the unsigned .

*/

int bitcount(unsigned x){

	int i;
	for(i=0; x !=0; x>>=1){
		if(x & 01){
			i++;
		}
	}

	return i;
}

int main(){

	int i;
	unsigned int a;

	a = ~0;
	
	for(i=0; i<10000L; i++){
		bitcount(a);
	}	
	printf("the number of 1-bit is: %d.\n", bitcount(a));

	return 0;

}

	
