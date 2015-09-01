#include "stdio.h"
#include "ctype.h"

/**

	convert a string to and double precision float number. 

*/

#define LINE_LIMIT	1024

double atof(const char* str){
	
	int index;
	char sign, signofexp;
	int	valueofexp; 
	double power;
	double result;


	/* ignore blanks. */
	index = 0;
	while(str[index] == ' '){	
		index++;
	}
	
	/* get the sign. */
	sign = str[index++] == '-'? -1 : 1;
	if(isdigit(str[index-1])){	
		index -= 1; 
	} 
	
	/* get the integer part of double. */
	result = 0.0;
	while(isdigit(str[index])){
		result = 10*result + str[index] - '0';	
		index++;
	}	
	
	/* get the fraction of the double. */
	if(str[index] == '.'){
		index++;
		power = 1.0;
		while(isdigit(str[index])){
			result = 10*result + str[index] - '0';	
			power *= 10;	
			index++;
		}
	}
	
	/* handle exp. */
	valueofexp = 0.0;
	if(str[index] == 'e' || str[index] == 'E'){
		index++;
		/* handle sign of exp. */
		signofexp = str[index++] == '-'? -1 : 1;
		if(isdigit(str[index-1])){	index -= 1; }	
		/* handle value of exp. */
		while(isdigit(str[index])){
			valueofexp = valueofexp*10 + str[index] - '0';	
			index++;
		}	
	}

	/* handle the power. */
	if(valueofexp > 0.0){
		for(index=0; index<(int)valueofexp; index++){
			power = signofexp > 0? power/10 : power*10;
		}
	}	

	return (result*sign/power);
}

/* get newline from input. */
int getnewline(char* line, const int limit){

	short c;
	int index;
	
	for(index=0; index < limit -1 && (c=getchar()) != EOF && c != '\n'; index++){
		line[index] = c;
	}

	if('\n' == c){
		line[index++] = c;
	}

	line[index] = '\0';

	return index;
}


int main(void){
	
	char line[LINE_LIMIT];

	while(getnewline(line, LINE_LIMIT) > 0){
		printf("the value of the line is: %lf\n", atof(line));
	}

	return 0;
}
