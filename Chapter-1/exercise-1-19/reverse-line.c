#include "stdio.h"

/**

	remove the trail blank in the line.

*/

#define SINGLE	0
#define MULTI		1

#define BUFFER_SIZE	1000

int getline_(char*, int);
void removeTrailBlank(char*);
void reverseLine(char*);

int main(){

	int len;
	char line[BUFFER_SIZE];

	while((len = getline_(line, BUFFER_SIZE)) > 0){
		removeTrailBlank(line);
		reverseLine(line);
		printf("%s", line);
	}

	return 0;
}

/* get a line from the input */
int getline_(char* str, int limit){

	short c;
	int cursor;

	for(cursor=0; cursor < limit-1 && (c=getchar())!=EOF && c!='\n'; cursor++){
		str[cursor] = c;
	} 

	if('\n' == c){
		str[cursor] = c;
		cursor++;
	}

	str[cursor] = '\0';

	return cursor;
}

/* remove the trail blank in the line */
void removeTrailBlank(char* line){

	short c;
	int cursor, counter;
	char flag;
	char state;
	char buffer[BUFFER_SIZE];

	flag = 1;
	counter = 0;
	state = SINGLE;
	for(cursor=0; (c=line[cursor]) != '\0'; cursor++){
		if(' ' == c || '\t' == c){
			if(SINGLE == state){
				buffer[counter++] = ' ';	
			}
			state = MULTI;
		}else if('\n' == c){
			if(1 == flag){
				buffer[0] = '\0';
				break;
			}else{
				buffer[counter++] = c;
			}
		}else if(MULTI == state){
			buffer[counter++] = c;
			state = SINGLE;	
		}else{
			buffer[counter++] = c;	
			if(1 == flag){
				flag = 0;
			}
		}
	}
	
	buffer[cursor] = '\0';

	cursor = 0;
	while((line[cursor] = buffer[cursor]) != '\0'){
		cursor++;
	}
}

/* 	reverse the line	*/
void reverseLine(char* line){

	int cursor;
	int len;
	char buffer[BUFFER_SIZE];

	for(len=0; line[len] != '\n'; len++){
		buffer[len] = line[len];	
	}

	for(cursor=0; cursor < len; cursor++){
		line[cursor] = buffer[len-cursor-1];
	}

	line[cursor++] = '\n';
	line[cursor] = '\0';
}	
	
