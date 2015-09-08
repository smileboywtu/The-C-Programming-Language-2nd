#include "stdio.h"

/**

	this program entab or detab the string and reveive the tab number
	you can use the arg to set the tab number or use default.

*/

int start;
int size;

void entab(char* str){

	int index;

	index = 0;	
	while(*(str+index)){
		if(index == start-1){
			while(size-- > 0){	putchar(' ');}
			putchar(*(str+index++));
		}else{	putchar(*(str+index++));}
	}	
}

void detab(char* str){

	short c;
	int index;

	index = 0;
	while((c=*(str+index))){
		if(index == start - 1){
			while(size-- > 0){
				if(c != ' '){	putchar(c);}
				// increase the index
				index++;
				c=*(str+index);
			}
		}
		else{	putchar(c);}
		index++;
	}
}
