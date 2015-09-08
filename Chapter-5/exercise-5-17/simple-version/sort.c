#include "function.h"

/**

	this program is the sort program for sorting string and numbers.

*/

int main(int argc, char* argv[]){

	extern char reverse;
	extern char directory;
	extern char ignorecase;

	extern int partseq;

	extern compare pf;

	short c;

	int index;
	int lineno;
	int linelen;
	char number;
	char keyword;
	char line[LINE_LIMIT];
	char* lines[LINE_NUMBER];

	number = 0;
	keyword = 0;
	while(--argc > 0 && (*++argv)[0] == '-'){
		while( (c=*++argv[0]) ){
			switch(c){
				case 'r':
					{ reverse = 1; break;}
				case 'n':
					{	number = 1; break;}
				case 'f':
					{ ignorecase = 1; break;}
				case 'd':
					{	directory = 1; break;}
				case 'k':
					{ keyword = 1; partseq= 0; break;} 
				case '1': case '2': case '3': case '4': case '5': case '6': case '7': case '8': case '9': case '0':
					{	if(keyword){	partseq = partseq* 10 + c - '0';} break;}
				default:
					{ printf("invalid flag\n"); break;}
			}
		}
	}

	if(argc != 0){

		printf("Usage: sort -r -n -f\n");
		return -1;
	}

	if(number == 1 && ignorecase == 1){
		printf("can not use -n and -f together\n");
		return -1;
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
		printf(number == 1 && keyword == 0? "%s\n" : "%s", lines[index]);
	}

	return 0;
}
