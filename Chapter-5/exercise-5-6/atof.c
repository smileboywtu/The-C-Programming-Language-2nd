#include "stdio.h"
#include "ctype.h"

/**

	convert a sting to float.

*/

double atof(const char* str){

	char sign;
	double power;
	double result;
	int index;

	index = 0;
	while(isspace(*(str+index))){	index++;}

	sign = *(str+index) == '-'? -1 : 1;

	if(*(str+index) == '-' || *(str+index) == '+'){
		index++;	
	}	

	result = 0;
	power = 1;
	while(isdigit(*(str+index))){
		result = result * 10 + *(str+index) - '0';
		index++; 
	}
	
	if(*(str+index) == '.'){
		index++;
		while(isdigit(*(str+index))){
			result = result * 10 + *(str+index) - '0';
			power *= 10;
			index++;
		}
	}
	
	return result * sign / power;
		
}


int main(void){

	char str0[] = "  -234";
	char str1[] = "-.678";

	printf("the float is %lf\n", atof(str0));
	printf("the float is %lf\n", atof(str1));

	return 0;
}	
