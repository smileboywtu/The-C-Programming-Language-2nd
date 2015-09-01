#include "stdio.h"
#include "ctype.h"

/**

	make the example never contains more than one character.

*/

#define EMPTY	-2

int buffer = EMPTY;

int getch(){

	int c;
	
	c = buffer != EMPTY ? buffer : getchar();
	buffer = EMPTY;

	return c;
}


void ungetch(int c){

	buffer = c;

}
