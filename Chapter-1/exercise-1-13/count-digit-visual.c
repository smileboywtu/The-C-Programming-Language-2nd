#include "stdio.h"

/**

	use the array to save the result.

*/
#define MAX_NUMBER 100000.0
#define MAX_MARK	 50

void showHistogram(long nCount){
	int i;
	long percentCount;
	percentCount = nCount/MAX_NUMBER*MAX_MARK;
	if(MAX_MARK < percentCount){
		percentCount = MAX_MARK;
	}
	printf("%8ld | ", nCount);
	for(i=0; i<percentCount; i++){
		putchar('*');
	}
	putchar('\n');
}
	
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

	// show the visual one
	for(i=0; i<10; i++){
		showHistogram(digits[i]);
	}

	showHistogram(whitespaces);
	showHistogram(others);	

	return 0;
}
