#include "stdio.h"
#include "ctype.h"

/**

	using a buffer to hold the data for getch and ungetch.  

*/

#define BUFFER_SIZE	1024

int buffer[BUFFER_SIZE];
int bp;

int getch(){
	return bp > 0? buffer[bp--] : getchar();
}

void ungetch(int c){
	buffer[++bp] = c;
}	

	
