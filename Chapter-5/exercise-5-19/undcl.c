#include "function.h"

/**

	this program undcl.

*/

int gettoken(void);

void undcl(void){

	extern char out[MAX_OUT_SIZE];
	extern char token[MAX_TOKEN_SIZE];

	int type;
	char ignore;
	char temp[MAX_TOKEN_SIZE];

	while(gettoken() != EOF){

		strcpy(out, token);
		ignore = 0;
		while(ignore || (type=gettoken()) != '\n'){
			
			ignore = 0;

			if(type == PARENS || type == BRACKETS){	strcat(out, token);}
			else if(type == '*'){
				if((type=gettoken()) != PARENS && type != BRACKETS){

					sprintf(temp, "*%s", out);
				}else{				

					sprintf(temp, "(*%s)", out);
				}
				ignore = 1;
				strcpy(out, temp);	
			}
			else if(type == NAME){
				sprintf(temp, "%s %s", token, out);
				strcpy(out, temp);
			}
			else{	printf("invalid input at %s\n", token);}
		}	

		printf("%s\n", out);
	}

}
