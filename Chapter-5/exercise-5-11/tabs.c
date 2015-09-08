#include "func.h"
#include "stdio.h"

/**

	this is the client for the entab and detab.

*/

void entab(char* str);
void detab(char* str);
int getnewline(char* line, const int limit);

int main(int argc, char* argv[]){

	extern int tabs;

	short c;
	char line[LINE_LIMIT];
	char entabflag, detabflag;

	tabs = 0;
	entabflag = 0;
	detabflag = 0;
	while(--argc > 0 && (*++argv)[0] == '-'){

		while((c=*++argv[0])){
			switch(c){
				case 'e':
					{	entabflag = 1;	break;}
				case 'd':
					{ detabflag = 1;  break;}
				case '0': case '1': case '2':  case '3': case '4': case '5': case '6': case '7': case '8': case '9':
					{ tabs = tabs * 10 + c - '0'; break;}
				default:
					{ printf("error flag for the program.\n"); break;}	
			}
		}	
	}

	if(argc > 0){
		printf("Usage: tabs -e|d -number\n");
		return -1;
	}

	if(entabflag == 1 && detabflag == 1){
		printf("You can just use flag -d or -e do not enable together.\n");
	}
	
	if(!tabs){
		tabs = TAB_NUMBER;
	}

	while(getnewline(line, LINE_LIMIT) > 0){

		if(entabflag){	entab(line);}
		else if(detabflag){	detab(line);}
		else{	printf("%s", line);}
	}

	return 0;
}

/* get new line from the command line. */
int getnewline(char* line, const int limit){

	short c;
	int index;

	index = 0;
	while(index < limit-1 && (c=getchar()) != EOF && c != '\n'){
		line[index++] = c;
	}

	if(c == '\n'){
		line[index++] = c;
	}

	line[index] = '\0';

	return index;
}
