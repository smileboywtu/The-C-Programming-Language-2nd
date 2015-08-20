#include "stdio.h"

int power(int m, int n);

int main(){

	int a, b;
	
	a = 2;
	b = 3;

	printf("The result for 2^3 is: %d\n", power(a, b));
		
	return 0;
}

/*	this function raise the base to n-th power */
int power(int base, int n){

	int i;
	int result;
	
	result = 1;
	for(i=0; i<n; i++){
		result *= base;
	}
	
	return result;
}
