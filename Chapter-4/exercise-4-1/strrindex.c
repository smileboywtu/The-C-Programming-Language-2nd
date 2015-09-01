#include "stdio.h"

/**

	this program return the rightmost occurrence of t in s.

*/


#define LINE_LIMIT	1024

/* get a line from the input. */
int getnewline(char* line, const int limit){

	short c;
	int index;

	for(index=0; index < limit-1 && (c=getchar()) != EOF && c != '\n'; index++){
		line[index] = c;
	}

	/* fill the new line mark. */
	if( '\n' == c){
		line[index++] = c;	
	}

	/* fill string end mark. */
	line[index] = '\0';

	return index;
}

/* return the right most occurrence of the t in s. */
int strrindex(const char* s, const char* t){
	
	int i, j, k;
	int occurrence;

	occurrence = -1;
	for(i=0; s[i] != '\0'; i++){
		for(j=i, k=0; s[j] == t[k] && s[j] != '\0' && t[k] != '\0'; j++, k++){	;	}
		if(t[k] == '\0'){
			occurrence = i;
		}
	}
	
	return occurrence;
}

int main(){

	char pattern[] = "hello";
	char line[LINE_LIMIT];

	printf("the pattern is %s\n", pattern);
	while(getnewline(line, LINE_LIMIT) > 0){
		printf("the right most occurrence of pattern in line is: %d\n", strrindex(line, pattern));
	}

	return 0;
}
