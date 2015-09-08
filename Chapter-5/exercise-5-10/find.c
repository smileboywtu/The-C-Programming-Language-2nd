#include "stdio.h"
#include "string.h"

/**

	this program find the patter in the string.

*/

#define LINE_LIMIT	1024

int getnewline(char* line, const int limit){

	short c;
	int index;
	
	index = 0;
	while(index<limit-1 && (c=getchar()) != EOF && c != '\n'){
		*(line+index++) = c;
	}

	if(c == '\n'){
		*(line+index++) = c;
	}

	*(line+index) = '\0';

	return index;
}

int main(int argc, char* argv[]){

	short c;
	int lineno;
	int except, number, found;
	char line[LINE_LIMIT];
	
	lineno = 0;
	except = 0;
	number = 0;
	found  = 0;

	while(--argc > 0 && (*++argv)[0] == '-'){
		while( (c = *++argv[0]) ){
			switch(c){
				case 'x':
					{	except = 1; break;}
				case 'n':
					{ number = 1; break;}
				default:
					{ printf("find: illegal option %c \n", c);	argc = 0; found = -1; break;}
			}
		}	
	}
	
	if(argc != 1){

		printf("Usage: find -x -n pattern\n");

	}else{
		while(getnewline(line, LINE_LIMIT) > 0){

			lineno++;

			if((strstr(line, *argv) != NULL) != except){
				if(number){
					printf("%d: ", lineno);
				}

				printf("%s", line);
				found++;
			}

		}
	}
	
	return found;
}
	
