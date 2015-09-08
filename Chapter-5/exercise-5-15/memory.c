#include "function.h"

/**

	this program will help to manage the memory for the program.

*/

static char allocbuf[FREE_SPACE];
static char* ap = allocbuf;

char* memalloc(int size){

	if(allocbuf + FREE_SPACE - ap >= size){
		ap += size;
		return ap - size;
	}
	
	printf("no enough memory for the space|n");

	return (char*)NULL;
}

void memfree(char* p){

	if(allocbuf <= p && p < ap){
		ap = p;
	}

	p = NULL;
}
