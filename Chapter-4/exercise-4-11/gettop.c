#include "stdio.h"
#include "ctype.h"
#include "operation.h"

/**
	
	get the top one of the stack.
	now this program can use +12.9	+.09	-3.9 -.89

*/
#define NUMBER 1  
#define BUFFER_SIZE	1024

static int bp;
static int buffer[BUFFER_SIZE];

#define GET_NEXT_CH		(bp>0? buffer[--bp] : getchar())
#define UN_GET_CH(c)	(buffer[bp++] = c)

char strcmpignorecase(const char* str1, const char* str2);

/* get the top one number or operator. */
int gettop(char* str){
	
	short c;
	short next;
	int index;

	// init
	index = 0;
	
	// ignore blanks
	while((str[index] = c = GET_NEXT_CH) == ' ' || c == '\t'){	;}

	// check before get next ch
	if(c == EOF || c == '\n'){
		return c;
	}

	next = GET_NEXT_CH;
	UN_GET_CH(next);

	/* get the number. */
	if(isdigit(c) || c == '.' || ((c == '-' || c == '+') && (isdigit(str[++index] = c = GET_NEXT_CH) || c == '.'))){
	
		if(isdigit(c)){
			while(isdigit(str[++index] = c = GET_NEXT_CH)){	;}
		}

		if(c == '.'){
			while(isdigit(str[++index] = c = GET_NEXT_CH)){	;}
		}
	
		str[index] = '\0';
		// give back
		if(c != EOF){ 	UN_GET_CH(c);}

		c = NUMBER;

	}else if(isalpha(c)){	// operator like sin, cos

		if(isalpha(next)){
	
			while(isalpha(str[++index] = c = GET_NEXT_CH)){ ;}
			str[index] = '\0';  // close the string 
			// give additional back
			if(c != EOF){ 	UN_GET_CH(c);}

		}


		if(strcmpignorecase(str, "SIN")){
			c = SIN;
		}else if(strcmpignorecase(str, "COS")){
			c = COS;
		}else if(strcmpignorecase(str, "EXP")){
			c = EXP;
		}else if(strcmpignorecase(str, "POW")){
			c = POW;
		}else if(index < 1){
			if(isupper(c)){
				c = VAR_SET;
			}else{
				c = VAR_GET;
			}
			str[++index] = '\0';
		}else{
			str[index] = '\0';
			c = -1;
		}

	}else{	// operator like +, -, *, /

		if(str[index-1] == '-' || str[index-1] == '+'){
			UN_GET_CH(str[index]);	
			c = str[index-1];
		}

		str[++index] = '\0';

	} 

	return c;	
}


/* compare the two string. */
char strcmpignorecase(const char* str1, const char* str2){
	
	int index;

	index = 0;	

	while(str1[index] != '\0' && str2[index] != '\0' && toupper(str1[index]) == str2[index]){	index++;}	

	return (str1[index] == '\0' && str2[index] == '\0') ? 1 : 0;

}
