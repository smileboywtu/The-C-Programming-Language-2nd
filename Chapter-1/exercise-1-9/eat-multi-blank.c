#include "stdio.h"

/**

	this program use to eat multi blank in the input stream.

*/

#define SINGLE 0
#define MULTI	 1

int main(){

	short c;
	char step;
	
	step = SINGLE;
	while(EOF != (c = getchar())){

		// machine state 1
		if(SINGLE == step){
			if(' ' == c){
				step = MULTI;
			}
		}

		// machine state 2
		else if(MULTI == step){
			if(' ' == c){
				continue;
			}else{
				step = SINGLE;
			}
		}

		putchar(c);
	}

	return 0;
}
	
