#include "stdio.h"
#include "ctype.h"

/**

	convert a sting to integer.

*/

int atoi(const char* str){

	char sign;
	int result;
	int index;

	index = 0;
	while(isspace(*(str+index))){	index++;}

	sign = *(str+index) == '-'? -1 : 1;

	if(*(str+index) == '-' || *(str+index) == '+'){
		index++;	
	}	

	result = 0;
	while(isdigit(*(str+index))){
		result = result * 10 + *(str+index) - '0';
		index++; 
	}
	
	return result*sign;
		
}


int main(void){

	char str0[] = "  -234";

	printf("the integer is %d\n", atoi(str0));

	return 0;
}	
