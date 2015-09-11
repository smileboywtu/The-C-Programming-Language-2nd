#include "function.h"

/**

	this is the main program to test the dcl.

*/


void	dcl(void);
int 	gettoken(void);

char error;

char out[MAX_OUT_SIZE];
char name[MAX_TOKEN_SIZE];
static char datatype[MAX_TOKEN_SIZE];


int main(void){

	extern int tokentype;
	extern char token[MAX_TOKEN_SIZE];
	
	while(gettoken() != EOF){

		strcpy(datatype, token);	// first token is the data type

		out[0] = '\0';
		
		dcl();

		if(tokentype != '\n' || error){

			printf("syntax error\n");
			error = 0;
			continue;
		}

		printf("%s: %s %s\n", name, out, datatype);

	}
	return 0;
}
