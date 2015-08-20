#include "stdio.h"

/**

	this program slice the long line into serveral lines.

*/

#define LINE_BUFFER				1024
#define LINE_PROPER_SIZE	50
#define WORD_PROPER_SIZE	16

#define IS_WORD		0
#define NON_WORD	1
#define OUT_ANY		2

int getline_(char*, int);
int isletter(char);
int getnextword(char*, int*, char*);

int main(){
	
 	int cursor;	
	char word[WORD_PROPER_SIZE];	
	char line[LINE_BUFFER];

	cursor = 0;
	while(getline_(line, LINE_BUFFER) > 0){
		printf("the source line is: %s\n", line);
		cursor = 0;
		while(getnextword(line, &cursor, word) > 0){
			printf("the cursor is: %d, the word is: %s\n", cursor, word); 
		}
	}
	
	return 0;
}

/*	get a line from the user command line */
int getline_(char* buffer, int limit){

	int i;
	short c;

	for(i=0; i<limit-1 && (c=getchar()) != EOF && c != '\n'; i++){
		buffer[i] = c;
	}

	if('\n' == c){
		buffer[i] = c;
		i++;
	}

	buffer[i] = '\0';

	return i;
}

/* justify if a character is a letter */
int isletter(char c){
	if(('a' <= c && c <= 'z') ||
		 ('A' <= c && c <= 'Z')){
		return 1;
	}	
	return 0;
}

/* get next word in a line. */
int getnextword(char* line, int* cursor, char* word){
	
	char c;	
	int next;
	int wordsize;
	int state;

	wordsize = 0;
	state = OUT_ANY;	
	for(next=*cursor; (c=line[next]) != '\0'; next++){
		if(wordsize < WORD_PROPER_SIZE){
			if(0 == wordsize){
				if(0 == isletter(c)){
					state = NON_WORD;
				}else{
					state = IS_WORD;
				}	
				word[wordsize++] = c;
			}else if((0 == isletter(c) && state == IS_WORD) ||
							 (1 == isletter(c) && state == NON_WORD)){
				break;
			}else{
				word[wordsize++] = c;
			} 
		}else{
			break;
		}					
	}	

	*cursor = next;
	word[wordsize] = '\0';
		
	return wordsize;
}

