#include "function.h"

/**


	this program sort the array of char* .

*/

char reverse;
char directory;
char ignorecase;

int partseq= -1;

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

void getrelavent(char* rela, const char* str){

	short c;
	char buffer[LINE_LIMIT] = {'\0'};
	char* pstr1 = buffer;
	const char* pstr2 = buffer;
	const	char* pstr3 = str;

	if(partseq > 1){

		int counter;
		char blankstate;

		// ignore space and tabs
		while((c=*str) && (c == ' ' || c == '\t')){	str++;}

		counter = partseq;
		blankstate = 0;
		while(counter > 1 && (c=*str)){
				
			if(c == ' ' || c == '\t'){	blankstate = 1;}
			else if(blankstate == 1){		counter--; blankstate = 0;}

			if( counter == 1 ){	break;}
			else{	str++;}	
		}
		
		// ignore space and tabs
		while((c=*str) && (c == ' ' || c == '\t')){	str++;}
		// copy the key part
		while((c=*str) && c != ' ' && c != '\t'){	*pstr1++ = c; str++;}		

		// here you must close the string
		*pstr1 = '\0';
	}
	else{	pstr2 = pstr3;}	

	if(cmpstr == pf){ // this means the user do not use -n flag
		while((c=*pstr2++)){
			if(isalpha(c) || c == ' ' || c == '\t'){	*rela++ = c;}	
		}			
	}else{
		while((c=*pstr2++)){
			if(isdigit(c) || c == ' ' || c == '\t'){	*rela++ = c;}	
		}			
	}
	
	// close rela
	*rela = '\0';
}
 
char partition(char* array[], const int low, const int high){

	int index;
	int biggerindex;

	char pivot[LINE_LIMIT];
	char relavent[LINE_LIMIT];

	char* pstr1;
	char* pstr2;

	pstr2 = array[high];
	if(directory || partseq > 1){
		getrelavent(pivot, array[high]);
		pstr2 = pivot;
	}

	for(index=0, biggerindex=0; index<high; index++){

		pstr1 = array[index];
		if(directory || partseq > 1){
			getrelavent(relavent, array[index]);
			pstr1 = relavent;			
		}

		if( ((*pf)(pstr1, pstr2) > 0 && reverse == 0) ||
				((*pf)(pstr1, pstr2) < 0 && reverse == 1) ){
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
