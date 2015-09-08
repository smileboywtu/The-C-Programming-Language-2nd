#include "stdio.h"
#include "number.h"


/**

	thie program will sort the string array in alpha order.

*/


void	afree(char* p);
char* allocmem(const int size);

void strcpy_(char* to, const char* from);
int getnewline(char* line, const int limit);
void quicksort(char* v[], const int low, const int high);

int main(void){

	int linesize;
	int indexofline;
	char linebuffer[LINE_LIMIT];
	char* lines[LINE_NUMBER] = {NULL};

	indexofline = 0;
	// get all new lines
	while((linesize=getnewline(linebuffer, LINE_LIMIT)) > 0){

		lines[indexofline] = allocmem(linesize+1);
		// copy to new memory
		strcpy_(lines[indexofline], linebuffer);		
		
		indexofline++;
	}

	// sort the line
	quicksort(lines, 0, indexofline-1);

	// show the new alpha order
	indexofline = 0;
	while(*(lines+indexofline) != NULL){

		printf("%s\n", *(lines+indexofline++));
	}		

	return 0;
}
