#include "stdio.h"

/**

	this program use to count the words from input.

*/

#define WORD_IN  0
#define WORD_OUT 1
	
int main(){

	short c;
	char step;
	int lines, words, chars;
	
	step = WORD_OUT;
	lines = words = chars = 0;
	
	while(EOF != (c = getchar())){
		chars++;
		if('\n' == c){
			lines++;
		}
		if(' ' == c || '\t' == c || '\n' == c){
			step = WORD_OUT;
		}else if(WORD_OUT == step){
			step = WORD_IN;
			words++;
		}
	}

	printf("%d chars, %d words, %d lines.\n", chars, words, lines);

	return 0;
}
