#include "function.h"

/**

	this program is the sort program for sorting string and numbers.

*/

int main(int argc, char* argv[]){

	extern char reverse;
	extern compare pf;

	short c;
	int index;
	int lineno;
	int linelen;
	char number;
	char line[LINE_LIMIT];
	char* lines[LINE_NUMBER];

	number = 0;
	while(--argc > 0 && (*++argv)[0] == '-'){
		while( (c=*++argv[0]) ){
			switch(c){
				case 'r':
					{ reverse = 1; break;}
				case 'n':
					{	number = 1; break;}
				default:
					{ printf("invalid flag\n"); break;}
			}
		}
	}

	if(argc != 0){

		printf("Usage: sort -r -n\n");
	}
	
	if(number == 1){
		pf = cmpnumber;
	}

	lineno = 0;
	while( (linelen = getnewline(line, LINE_LIMIT)) ){

		lines[lineno] = memalloc(linelen + 1);
		strcpy(*(lines+lineno++), line);
	}

	quicksort(lines, 0, lineno-1);

	for(index=0; index<lineno; index++){
		printf(number == 1? "%s\n" : "%s", lines[index]);
	}

	return 0;
}
