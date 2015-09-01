#include "stdio.h"
#include "ctype.h"
#include "assert.h"
#include "string.h"

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
	assert(bp < BUFFER_SIZE-1);
	buffer[++bp] = c;
}	

char ungets(const char* str){
	
	if(strlen(str) > BUFFER_SIZE - bp){
		return 0;
	}
	
	int index;

	index = 0;
	while(str[index] != '\0'){
		buffer[++bp] = str[index];	
		index += 1;
	}
	
	return 1;

}

	
