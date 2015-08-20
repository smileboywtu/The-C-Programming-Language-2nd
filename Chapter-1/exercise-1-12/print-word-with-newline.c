#include "stdio.h"

/**

	print a word with newline.

*/

#define WORD_IN 	0
#define WORD_OUT	1

int main(){

	short c;
	char step;
	
	step = WORD_OUT;
	while(EOF != (c = getchar())){
		if(' ' == c || '\t' == c || '\n' == c){
			if(WORD_IN == step){
				putchar('\n');
			}
			step = WORD_OUT;
		}else if(WORD_OUT == step){
			step = WORD_IN;
		}
		
		putchar(c);
	}

	return 0;

}
		
