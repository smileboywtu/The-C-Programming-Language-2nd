#include "function.h"


/**


	this program sort the array of char* .

*/

char reverse;
char ignorecase;
compare pf = cmpstr; 

#define SWAP(t, a, b)		\
{												\
	t	tempvalue;					\
	tempvalue = a;				\
	a = b;								\
	b = tempvalue;				\
}												\

int cmpnumber(char* str1, char* str2){

	double a, b;

	a = atof(str1);
	b = atof(str2);

	if(a > b)	return 1;
	else if( a == b ) return 0;
	else	return -1;
}

int cmpstr(char* str1, char* str2){
	return ignorecase? strcasecmp(str1, str2) : strcmp(str1, str2);
}
 
char partition(char* array[], const int low, const int high){

	int index;
	int biggerindex;

	char* pivot = array[high];
		
	for(index=0, biggerindex=0; index<high; index++){
		if( ((*pf)(array[index], pivot) > 0 && reverse == 0) ||
				((*pf)(array[index], pivot) < 0 && reverse == 1) ){
			SWAP(char*, array[index], array[biggerindex])
			biggerindex++;
		}
	}	
	// fill the position
	SWAP(char*, array[biggerindex], array[high])

	return biggerindex;
}

void quicksort(char* array[], const int low, const int high){

	int part;

	if(low < high){
		
		part = partition(array, low, high);
		quicksort(array, low, part - 1);
		quicksort(array, part + 1, high);	
	}
}
