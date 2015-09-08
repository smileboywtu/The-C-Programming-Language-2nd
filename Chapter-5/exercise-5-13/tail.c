#include "string.h"
#include "function.h"

/**

	this program print the last n lines from the input.

*/

int main(int argc, char* argv[]){

	short c;
	int lineno;
	int linelen;
	int toprint;
	char linebuffer[LINE_LIMIT];
	char*	lines[LINE_NUMBER];

	toprint = -1;
	while(--argc > 0 && (*++argv)[0] == '-'){
		while((c=*++argv[0])){
			switch(c){
				case '0': case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9':
					{	if(toprint == -1){ toprint = 0;} toprint = toprint * 10 + c - '0'; break;}
				default:
					{	printf("unknow flags to the tail.\n"); break;}
			}
		}	
	}

	if( argc != 0 || toprint == -1){
		printf("Usage: tail -n\n");
		return -1;
	}

	lineno = 0;
	while((linelen=getnewline(linebuffer, LINE_LIMIT)) > 0){	
		lines[lineno] = memalloc(linelen+1);	
		strcpy(lines[lineno++], linebuffer);
	}
	
	while(toprint-- > 0){
		if(--lineno >= 0){
			printf("%d: %s", lineno+1, lines[lineno]);	
		}
	}	

	return 0;
}


