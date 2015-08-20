#include "stdio.h"


/**
	this program is used to test the '\b' to eat a line, but it can't.

*/

int len(char* str);

int main(){

	int i;
	int len2;

	char* str1;
	char* str2;
	char* str3;

	str1 = "hello, smile.";
	str2 = "hello, John.";
	str3 = "would you like eatting with me?";

	len2 = len(str2);

	puts(str1);
	puts(str2);

	for(i=0; i<len2+2; i++){
		putchar('\b');
	} 

	putchar(' ');
	printf("%s", str3);

	return 0;
}

int len(char* str){

	int i;
	int counter;

	counter = 0;
	for(i=0; *(str+i) != '\0'; i++){
		counter++;
	}
	
	return counter;
}
