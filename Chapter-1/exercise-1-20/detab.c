#include "stdio.h"

/**
	
	this program replace the tab with equal length of blank.

*/

#define TAB_STOP	4	// this is the normal size of tab in serveral OS.

void fillWithBlank(){

	char i;

	for(i=0; i<TAB_STOP; i++){
		putchar(' ');
	}
}

int main(){


	short c;

	while(EOF != (c=getchar())){

		if('\t' == c){
			fillWithBlank();
		}else{
			putchar(c);
		}
	}
	
	return 0;
}

			
