#include "stdio.h"

/**

	this program copy the first n character in string from to string to.

*/

void strncpy_(char* to, const char* from, const int n){

	int index;

	index = 0;
	
	while(index++ < n && (*to++=*from++)){	;}

	*to = '\0';

}


int main(void){


	char to[128];
	char from[] = "hi, are you ok?";

	strncpy_(to, from, 2);

	printf("after copy 2 characters, the string is %s\n", to);

	return 0;

}
