#include "stdio.h"

/**

	use this program to count the blank and tabs from the input stream.

*/


int main(){

	short c;
	int blanks, tabs;

	blanks = 0;
	tabs = 0;

	while(EOF != (c = getchar())){

		if('\t' == c){
			tabs++;
		}else if(' ' == c){
			blanks++;
		}else{
			;
		}
	}	

	printf("Input text contains %d blanks and %d tabs.\n", blanks, tabs);

	return 0;
}
