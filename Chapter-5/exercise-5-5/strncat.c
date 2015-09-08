#include "stdio.h"

/**

	this program only copy the first n charater in string t to the end of string s.

*/

void strncat_(char* to, const char* from, const int n){

	int index;

	// get the end of to
	while((*to++)){	;}
	to--;

	index = 0;
	while(index++ < n && (*to++ = *from++)){	;}

	*to = '\0';	
			
}

int main(void){

	char to[128] = "are you ok?";
	char from[] = "Joker, something wrong with my computer.";

	printf("the source string is %s\n", to);

	strncat_(to, from, 5); 

	printf("after catch, the string is %s\n", to);

	return 0;
}
