#include "stdio.h"

/**

	this program test the const qualifier.

*/

int strlen_(const char* str){

	int i;

	i = 0;
	while(str[i] != '\0'){
		i++;
	}

	return i;
}

int main(){

	int *p;
	char *c;

	const int a = 3;
	const char greed[] = "hello";

	p = &a;
	c = greed;

	*(c+2) = 'x';
	*p = 5;

	printf("the value is: %d\n", a);
	printf("the greed for you: %s, the len is: %d\n", greed, strlen_(greed));

	return 0;

}
