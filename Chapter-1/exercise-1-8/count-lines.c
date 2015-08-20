#include "stdio.h"

/**

	count the user input lines.

*/

int main(){

	short c;
	int lines;

	lines = 0;
	while(EOF != (c = getchar())){
		if('\n' == c)
			lines++;
	}
	
	printf("User input %d lines.\n", lines);

	return 0;
}
