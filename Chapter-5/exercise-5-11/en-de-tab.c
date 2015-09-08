#include "func.h"
#include "stdio.h"

/**

	this program entab or detab the string and reveive the tab number
	you can use the arg to set the tab number or use default.

*/

int tabs = TAB_NUMBER;

void detab(char* str){

	short c;
	
	while((c=*str++)){
		if(c == '\t'){
			while(tabs-- > 0){
				putchar(' ');	
			}
		}else{
			putchar(c);	
		}
	}	
}

void entab(char* str){

	short c;
	int blanks;

	blanks = 0;	
	while((c=*str++)){
		if(blanks == tabs-1 && c == ' '){		putchar('\t'); }
		else if(c == ' '){	blanks++; }
		else if(blanks > 0 && c != ' '){
			while(blanks-- > 0){
				putchar(' ');
			}
			putchar(c);
		}
		else{	putchar(c); }
	}
}

