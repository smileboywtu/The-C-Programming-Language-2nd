#include "stdio.h"


/**

	check if string t is end of string s.
	this program can also get the occurrence times of t in s.

*/

char strend_(const char* str, const char* end){

	int indexofstr, indexofend;
	int lenofstr, lenofend;
	
	/* get len first. */
	lenofstr = 0;
	while((*(str+lenofstr++))){	;}
	lenofend = 0;
	while((*(end+lenofend++))){	;}

	indexofstr = lenofstr-1;
	indexofend = lenofend-1;
	
	while(indexofstr>=0 && indexofend>=0 && *(str+indexofstr--) == *(end+indexofend--)){	;}

	if(indexofend == -1){
		return 1;
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
