#include "stdio.h"

/**

	copy the string t to the end of string s.

*/

void strcat_(char* s, const char* t){

	// find the end of str s
	while(*s++){	;}

	// copy
	while((*s++ = *t++)){	;}

}


int main(void){

	char s[128] = "hi, I'm smile boy.";
	char t[] = "nice to meet you.";

	printf("the source s is: %s\n", s);

	strcat_(s, t);

	printf("after copy t to the end of s: %s\n", s);

	return 0;
}
