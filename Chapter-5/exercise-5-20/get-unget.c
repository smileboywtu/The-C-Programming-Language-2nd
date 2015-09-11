#include "stdio.h"

/**

	this program can get and unget a character from the input stream.

*/

#define BUFFER_SIZE	1024

char streambuffer[BUFFER_SIZE];
int  sc = 0;

int getch(void){
	
	return sc > 0? streambuffer[--sc] : getchar();

}

void ungetch(int c){

	streambuffer[sc++] = c;

} 

	
