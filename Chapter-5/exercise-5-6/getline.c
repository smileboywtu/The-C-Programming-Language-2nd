#include"stdio.h"

/**

	this program use pointer to get the new line.

*/

#define LINE_LIMIT	1024

int getline_(char* line, const int limit){

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

int main(void){

	char line[LINE_LIMIT] = {0};

	while(getline_(line, LINE_LIMIT)>0){
		printf("%s", line);
	}	

	return 0;
}
