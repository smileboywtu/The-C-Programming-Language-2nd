#include "stdio.h"

/**

	this program test the argc and argv.

*/

int main(int argc, char* argv[]){

	while(--argc > 0){
		printf(argc>0?"%s ":"%s", *++argv);
	}

	printf("\n");

	return 0;
}
