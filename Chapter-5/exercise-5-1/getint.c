#include"ctype.h"
#include"stdio.h"


/**

	this program get int from the input stream.

*/


int getch( void );
void ungetch( int c );

/*	get an integer from the stream. */
int getint(int* p2i){

	short c;
	short next;
	char  sign;

	// ignore space
	while(isspace(c=getch())){	;}

	if(c == EOF){
		return c;
	}

	next = getch();
	ungetch(next);

	if(isdigit(c) || ((c == '-' || c == '+') && isdigit(next))){
		
		// get the sign
		sign = c == '-'? -1 : 1;	

		if(c == '-' || c == '+'){
			c = getch();
		}

		*p2i = 0;
		do{

			*p2i = *p2i*10 + c - '0';
			// get next
			c = getch();
		}while(isdigit(c));

		*p2i *= sign;

	}
	
	if(c != EOF){
		ungetch(c);
		return 0;
	}

	return c;
}
