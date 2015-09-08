#include "ctype.h"
#include "stdio.h"

/**

	use the array to save the lines.

*/

#define LINE_LIMIT	1024
#define LINE_NUMBER	100

int getnewline(char* line, const int limit);

int main(void){
	
	int cursor;
	int indexofline;
	char lines[LINE_NUMBER][LINE_LIMIT];
	
	indexofline = 0;
	while(getnewline(lines[indexofline], LINE_LIMIT)){	indexofline++;}

	cursor=0;
	for(cursor=0; cursor<indexofline; cursor++){
		printf("index %d of lines is %s.", cursor, lines[cursor]);
	}
	
	return 0;
}

		
