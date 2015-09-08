#include "stdio.h"

/**

	this program use the pointer to reverse the string.

*/

void reverse(char* str){

	int len;
	int index;
	char tempvalue;

	len = 0;
	while(*(str+len) != '\0'){	len++;}	
	len--;

	for(index=0; index<len-index; index++){
		tempvalue = *(str+index);
		*(str+index) = *(str+len-index);
		*(str+len-index) = tempvalue;
	}	
		
}

int main(void){

	char str[] = "0123456789";

	printf("source str is %s\n", str);

	reverse(str);

	printf("after reverse: %s\n", str);

	return 0;
}
