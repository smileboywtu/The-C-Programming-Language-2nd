#include "stdio.h"

/**
	
	this program replace the string of blank with the tabs and blank.

*/

#define TAB_STOP	4		// this is the normal size of tab in serveral OS.

#define BLANK_IN	0
#define BLANK_OUT	1

void fillWithTab(int nCount){
	while(nCount-- > 0){
		putchar('\t');
	}
}

void fillWithBlank(char nCount){

	while(nCount > 0){
		putchar(' ');
		nCount--;
	}
}

int main(){
	
	short c;
	char state;
	char counter;
	
	state = BLANK_OUT;
	counter = 0;
	while(EOF != (c=getchar())){
		if(' ' == c || '\t' == c){
			if(BLANK_OUT == state){
				state = BLANK_IN;
			}
			counter++;
		}else if(BLANK_IN == state){
			fillWithTab(counter/TAB_STOP);
			fillWithBlank(counter%TAB_STOP);
			counter = 0;
			state = BLANK_OUT;
		}else{
			putchar(c);
		}		
	}
	return 0;

}
