#include "stdio.h"
#include "ctype.h"

/**

	using a buffer to hold the data for getch and ungetch.  

*/

int getnewline(int* line, const int limit){

	int c;
	int index;

	index = 0;
	while(index < limit - 1 && (c = getchar()) != EOF && c != '\n'){
		line[index++] = c;
	}

	line[index++] = c;

	line[index] = '\0';

	return index;
}
	
