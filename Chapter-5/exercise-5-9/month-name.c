#include "stdio.h"

/** 
	
	this program will tell the month name.

*/

const char* monthName(const int month){

//	char *pstr = "hello";

	static const char* const MONTHNAME[] = {
		"ILLEGAL",
		"January",
		"Fabruary",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"Septempber",
		"October",
		"November",
		"December"
	};

//	MONTHNAME[5] = pstr;

	return month < 1 || month > 12? MONTHNAME[0] : MONTHNAME[month];
}

int main(void){

	int index;

	for(index=1; index < 13; index++){

		printf("the name of month %d is %s\n", index, monthName(index));
	}

	return 0;
}
