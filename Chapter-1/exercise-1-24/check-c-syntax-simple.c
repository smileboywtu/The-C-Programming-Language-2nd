#include "stdio.h"
#include "check.h"

/**
	
	this program used to check the syntax error in the source c file.

*/

int main(){

	if(1 == checksyntax()){
		printf("the source file checked ok.\n");
	}else{
		printf("there are errors in the source file.\n");
	}

	return 0;
}
