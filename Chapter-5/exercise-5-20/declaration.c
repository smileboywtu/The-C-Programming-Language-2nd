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
	static char paramtype = 0;

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
	while((type=gettoken()) == PARENS || type == BRACKETS || type == NAME || type == '(' || type == ',' || type == ')'){

		if(PARENS == type){	

			strcat(out, " function returning");
		}
		else if(type == NAME){
			
			if(!paramtype){

				strcat(out, " ");
				strcat(out, token);	
				strcat(out, " type param");
				paramtype = 1;
			}
			else if(paramtype){

				strcat(out, " named ");
				strcat(out, token);	
				paramtype = 0;
			}
		}
		else if(type == '('){
			
			strcat(out, " function which has");					
			paramtype = 0;
		}
		else if( type == ','){

			strcat(out, " , ");
			paramtype = 0;
		}
		else if( type == ')'){
			
			strcat(out, " returning");
			paramtype = 0;
		}
		else if(BRACKETS == type){

			strcat(out, " array");
			strcat(out, token);
			strcat(out, " of");	
		}
	}	

}
