#include "stdio.h"


/**

	make the slice mark visiable.

*/

#define V_TAB				putchar('\\');putchar('t');
#define V_BACKSPACE putchar('\\');putchar('b');
#define V_BACKSLASH	putchar('\\');putchar('\\');

int main(){

	short c;

	while(EOF != (c = getchar())){

		if('\t' == c){
			V_TAB
		}else if('\b' == c){
			V_BACKSPACE
		}else if('\\' == c){
			V_BACKSLASH
		}else{
			putchar(c);
		}

	}

	return 0;
} 
