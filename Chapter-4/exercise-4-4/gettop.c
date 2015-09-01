#include "stdio.h"
#include "ctype.h"

/**
	
	get the top one of the stack.
	now this program can use +12.9	+.09	-3.9 -.89

*/
#define NUMBER 1  

int getch(void);
void ungetch(int c);

/* get the top one number or operator. */
int gettop(char* str){
	
	short c;
	int index;

	// init
	index = 0;
	
	// ignore blanks
	while((str[index] = c = getch()) == ' ' || c == '\t'){
		;
	}
	
	// check
	if(!isdigit(c) && c != '.'){  // this will allow number write like .234
		if((c == '-' || c == '+') && (isdigit((c=getch())) || c == '.')){
			str[++index] = c;	
		}else{ 
			if(str[index] == '-' || str[index] == '+'){
				ungetch(c);
				c = str[index];
			}
			str[++index] = '\0';
			return c;		// this can be an eof	
		}
	}

	/* get the number. */
	if(isdigit(c) || c == '-' || c == '+'){
		while(isdigit(str[++index] = c = getch())){
			;
		}
	}	

	if(c == '.'){
		while(isdigit(str[++index] = c = getch())){
			;
		}
	}
		
	// close the str
	str[index] = '\0';
	
	// do not get the next one.
	if( c != EOF ){
		ungetch(c);
	}

	return NUMBER;	
}


