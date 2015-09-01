#include "stdio.h"
#include "ctype.h"
#include "operation.h"

/**
	
	get the top one of the stack.
	now this program can use +12.9	+.09	-3.9 -.89

*/
#define NUMBER 1  

#define LINE_LIMIT	1024

int line[LINE_LIMIT];
int linecursor = 0;

int getnewline(int* line, const int limit);
char strcmpignorecase(const char* str1, const char* str2);

/* get the top one number or operator. */
int gettop(char* str){
	
	short c;
	short next;
	int index;

	/* get new line. */
	if(line[linecursor] == '\0'){
		getnewline(line, LINE_LIMIT);
		linecursor = 0;
	}

	index = 0;
	// ignore blanks
	while((str[index] = c = line[linecursor++]) == ' ' || c == '\t'){	;}

	next = line[linecursor];

	/* get the number. */
	if(isdigit(c) || c == '.' || ((c == '-' || c == '+') && (isdigit(str[++index] = c = line[linecursor++]) || c == '.'))){
	
		if(isdigit(c)){
			while(isdigit(str[++index] = c = line[linecursor++])){	;}
		}

		if(c == '.'){
			while(isdigit(str[++index] = c = line[linecursor++])){	;}
		}
	
		str[index] = '\0';
		// give back
		if(c != EOF){ 	linecursor--;}

		c = NUMBER;

	}else if(isalpha(c)){	// operator like sin, cos

		if(isalpha(next)){
	
			while(isalpha(str[++index] = c = line[linecursor++])){ ;}
			str[index] = '\0';  // close the string 
			// give additional back
			if(c != EOF){ 	linecursor--;}

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
			linecursor--;	
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
