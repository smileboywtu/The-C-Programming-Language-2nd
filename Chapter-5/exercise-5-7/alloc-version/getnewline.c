#include "ctype.h"
#include "stdio.h"

/**

	this program get the new line form the use input stream.

*/

int getnewline(char* line, const int limit){

	short c;
	int index;

	index = 0;
	while(index < limit -1 && (c=getchar()) != EOF && c != '\n'){

		*(line+index++) = c;
	}
	
	if(c == '\n'){
		*(line+index++) = c;
	}	
	
	*(line+index) = '\0';

	return index;
}
