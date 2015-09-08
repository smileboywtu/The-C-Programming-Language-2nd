#include "stdio.h"
#include "function.h"

/**

	this program get the new line form the command line.

*/

int getnewline(char* line, const int limit){
	
	short c;
	int index;

	index = 0;
	while(index < limit - 1 && (c=getchar()) != EOF && c != '\n'){
		*(line+index++) = c;
	}

	if('\n' == c){
		*(line+index++) = c;
	}

	*(line+index) = '\0';

	return index;
}
