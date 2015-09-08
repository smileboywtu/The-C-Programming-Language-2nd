#include"ctype.h"
#include"stdio.h"

/**

	this program get and unget a char from the stream.

*/

#define BUFFER_SIZE 1024

static int buffer[BUFFER_SIZE];
static int bp;


/* get a char */
int getch( void ){

	return bp > 0? buffer[--bp] : getchar();

}


/* unget a char. */
void ungetch( int c ){

	if(bp < BUFFER_SIZE){

		buffer[bp++] = c;
	}else{

		printf("the buffer is full!\n");
	}

}
