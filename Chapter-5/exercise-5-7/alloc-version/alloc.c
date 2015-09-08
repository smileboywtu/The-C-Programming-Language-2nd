#include "stdio.h"
#include "number.h"

/**

	this program will manage the space for the string sort program.

*/

static char allocbuffer[FREESPACE];
static char* fp = allocbuffer;

char* allocmem(const int size){

	if(allocbuffer+FREESPACE-fp >= size){

		fp += size;
		return fp-size;
	}else{
		
		printf("not enough memory.\n");
		return NULL;
	}

}	
	
void afree(char *p){
	if(p >= allocbuffer && p < allocbuffer + FREESPACE){
		fp = p;
	}
	/* make sure the memory return NULL */
	p = NULL;
}
	
