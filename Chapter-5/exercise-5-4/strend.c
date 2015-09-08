#include "stdio.h"


/**

	check if string t is end of string s.
	this program can also get the occurrence times of t in s.

*/

char strend_(const char* str, const char* end){

	char c;
	
	const char *pstr, *pend;

	while((c=*str++)){

		pstr = str;
		pend = end;
	 
		if(c == *pend++){

			while((c = *pstr++) == *pend++ && c != '\0'){	;}
			if(c == '\0'){
				return 1;
			}	
		}		
	}				

	return 0;
}

int main(void){


	char str0[] = "hello, my name is John";
	char str1[] = "nice to meet you, John";
	char str2[] = "nice to meet you, Tom";
	char str3[] = "John";

	if(strend_(str0, str3)){
		printf("John is the end if str0\n");
	}

	
	if(strend_(str1, str3)){
		printf("John is the end if str1\n");
	}


	if(strend_(str2, str3)){
		printf("John is the end if str2\n");
	}

	return 0;
}
