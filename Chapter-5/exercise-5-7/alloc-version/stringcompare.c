#include "ctype.h"

/**

	this program show how to compare two string.

*/

// if a < b -1
// if a = b 0
// if a > b 1
char strcmpignorecase(const char* str1, const char* str2){

	while(tolower(*str1) == tolower(*str2)){
		str1++;
		str2++;
	}	

	if(*str1 == '\0' &&  *str2 == '\0'){	return 0;}
	else if( tolower(*str1) > tolower(*str2)){	return 1;}
	else{	return -1;}

}

void strcpy_(char* to, const char* from){

	while((*to++=*from++)){	;}
}
