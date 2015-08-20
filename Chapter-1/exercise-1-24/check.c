#include "stdio.h"
#include "check.h"
#include "comments.h"

/**

	this program use to check the syntax error in c source file.

*/
#define MAX_CHECK_SET_SIZE	8	

Stack s;

/* check set. */
ElemType checkset[MAX_CHECK_SET_SIZE] = {
	34, 39, 40, 41, 91, 93, 123, 125	
};

void testtool(){
	
	/* just for test. */
	while(s.size > 0){
		putchar(pop(&s));
		putchar('\n');
	}
}

/* check if the elem is pair. */
char ispair(ElemType e){

	if(s.size == 0){
		return 0;
	}

	ElemType top;

	top = peek(&s);

	if((top == '\'' && e == '\'')	||
		 (top == '"' && e == '"')	||
		 (top == '(' && e == ')')	||
		 (top == '[' && e == ']')	||
		 (top == '{' && e == '}')	){
		
		return 1;
	}else{
		return 0;
	}
	
}

/* contain in the check set. */
char isincheckset(ElemType e){

	short cursor;
	for(cursor=0; cursor<MAX_CHECK_SET_SIZE; cursor++){
		if(e == checkset[cursor]){
			return cursor;
		}
	}

	return -1;
}

/* main func to check the source file. */
char checksyntax(){
	
	short c;
	extern Stack s;
	
	initstack(&s);
	while(EOF != (c=getchar())){
		if(1 == isInComments(c)){
			;
		}else if(-1 != isincheckset(c)){
			if(1 == ispair(c)){
				pop(&s);
			}else if(s.size >0 && '"' == c && '\'' == peek(&s)){
				;
			}else{
				push(&s, c);
			}
		}
	}

	/* default return. */
	if(s.size == 0){
		return 1;
	}else{
		testtool();
		return 0;
	}

}

