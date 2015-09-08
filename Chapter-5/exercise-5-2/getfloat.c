#include"ctype.h"
#include"stdio.h"
#include"flag.h"


/**

	this program get int from the input stream.

*/


int getch( void );
void ungetch( int c );

/*	get an integer from the stream. */
int getfloat(float* p2f){

	short c;
	short next;
	short power;
	char  sign;

	// ignore space
	while(isspace(c=getch())){	;}
	
	// you must check whether there is next char first.
	if( c == EOF ){
		return c;
	}

	next = getch();
	ungetch(next);

	if(isdigit(c) || c == '.' || ((c == '-' || c == '+') && (next == '.' || isdigit(next)))){
		
		// get the sign
		sign = c == '-'? -1 : 1;	

		if(c == '-' || c == '+'){
			c = getch();
		}

		*p2f = 0;
		power = 1;
		// deal with the number start with digit or .
		if(isdigit(c)){

			do{
				*p2f = *p2f*10 + c - '0';
			}while(isdigit(c=getch()));
				
		}

		if(c == '.'){
			
			while(isdigit(c=getch())){
				*p2f = *p2f*10 + c - '0';
				power *= 10;
			}	
		}
				
		*p2f *= sign;
		 
		if(power > 0){
			*p2f /= power;
		}

		ungetch(c);
		
		return NUMBER;
	}
	
	// if the current char is not a valid number elements, just estimate fromt the stream.
	// do not ungetch c
	return INVALID;	

}
