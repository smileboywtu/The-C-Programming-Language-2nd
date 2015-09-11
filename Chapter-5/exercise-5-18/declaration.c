#include "function.h"

/**

	this program deal with the declaration and direct-declaration.

*/

int gettoken(void);

void dcl(void);
void dirdcl(void);

/* parse a declaration. */
void dcl(void){

	extern char out[MAX_TOKEN_SIZE];

	int ns;

	ns = 0;
	while(gettoken() == '*'){
		ns++;
	}

	dirdcl();

	while(ns-- > 0){
		strcat(out, " pointer to");
	}

}

/* parse a direct declaration. */
void dirdcl(void){
		
	extern char error;
	extern int 	tokentype;
	extern char token[MAX_TOKEN_SIZE];
	extern char out[MAX_TOKEN_SIZE];
	extern char name[MAX_TOKEN_SIZE];

	int type;

	if(tokentype == '('){
		
		dcl(); // check if dcl

		if(tokentype != ')'){	//check errors
			error = 1;
			printf("error: missing )\n");
		}
	}

	else if(tokentype == NAME){

		strcpy(name, token);
	}

	else{
	
		error = 1;
		printf("error: expected name of (dcl)\n");
	}

	// after you get the name, you will get func type or array type.
	while((type=gettoken()) == PARENS || type == BRACKETS){

		if(PARENS == type){	
			strcat(out, " function returning");
		}
		else{
			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");	
		}
	}	

}
