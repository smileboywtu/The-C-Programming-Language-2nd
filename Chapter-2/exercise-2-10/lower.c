#include "stdio.h"

/**

	lower case use the conditional expression.

*/

int lower(int c){

	return 'A' <= c && c <='Z'? c+'a'-'A' : c;

}

int main(){

	int a;

	a = 'F';


	printf("a is %c.\n", lower(a));

	return 0;

}
