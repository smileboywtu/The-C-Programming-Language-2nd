#include "stdio.h"

/**
	
	this program used to get the longest line.

*/
#define BUFFER_SIZE	1000

int getline_(char*, int);
void copy(char*, char*);

int main(){

	int len;
	int longest;
	char currentline[BUFFER_SIZE];
	char longestline[BUFFER_SIZE];

	longest = 0;
	while( 0 < (len = getline_(currentline, BUFFER_SIZE)) ){
		printf("the current line is %s, contains %d characters.\n", currentline, len);
		if(len > longest){
			copy(currentline, longestline);
			longest = len;
		}
	}

	if(longest > 0){
		printf("the longest line is %s, contains %d characters.\n", longestline, longest);
	}

	return 0;
}

int getline_(char* str, int limit){

	short c;
	int cursor;

	cursor = 0;
	for(cursor=0; cursor<limit-1 && (c=getchar()) != EOF && c != '\n'; cursor++){
		str[cursor] = c;
	}

	if('\n' == c){
		str[cursor++] = c;
	}

	str[cursor] = '\0';

	return cursor;
}

void copy(char* from, char* to){

	int i;

	i = 0;
	while((to[i] = from[i]) != '\0'){
		i++;
	}
}	

	
