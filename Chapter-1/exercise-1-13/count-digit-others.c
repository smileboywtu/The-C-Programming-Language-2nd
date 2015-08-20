#include "stdio.h"

/**

	use the array to save the result.

*/

int main(){

	short c;

	int whitespaces, others;
	int digits[10];

	int i;

	whitespaces = 0;
	others = 0;
	
	for(i=0; i<10; i++)
		digits[i] = 0;
	
	while(EOF != (c = getchar())){
		if(c >= '0' && c <= '9'){
			++digits[c-'0'];
		}else if(' ' == c || '\n' == c || '\t' == c){
			++whitespaces;
		}else{
			++others;
		}
	}

	printf("Digits = ");
	for(i=0; i<10; i++)
		printf(" %d",digits[i]);
	printf(", white space = %d, other = %d\n", whitespaces, others);

	return 0;
}
