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

#define SINGLE		3
#define MULTI			4

int getline_(char*, int);
int isletter(char);
int getnextword(char*, int*, char*);
void slice(char*, int);
void removetrailblank(char*);

int main(){
	
	char line[LINE_BUFFER];

	while(getline_(line, LINE_BUFFER) > 0){
		removetrailblank(line);
		slice(line, LINE_PROPER_SIZE);
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

/* remove trail blank */
void removetrailblank(char* line){

	short c;
  int cursor, counter;
  char flag;
  char state;
  char buffer[LINE_BUFFER];
 
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

/* slice the long line into serveral line. */
void slice(char* line, int lsize){
	
	int cursor;
	short counter;
	short wordlen;
	char nextword[WORD_PROPER_SIZE];
	
	cursor = 0;
	counter = 0;
	while('\0' != line[cursor]){

		wordlen = getnextword(line, &cursor, nextword);
	 	
		/* try to check the lsize */
		if((0 == (cursor - wordlen)) || ((counter+wordlen) <= lsize)){
			counter += wordlen;
			printf("%s", nextword);				
		}else{
			if(0 == isletter(nextword[0])){
				printf("%s", nextword);
				putchar('\n');
				counter = 0;
			}else{
				/* move to a newline */
				putchar('\n');
				printf("%s", nextword);
				counter = wordlen;
			}
		}	
	}	

}	
