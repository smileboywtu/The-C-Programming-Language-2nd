#include "stdio.h"

/**
	list for escape sequence.
	
  \a	alert(bell)
	\b 	backspace
	\f 	formfeed
	\n	newline
	\r 	carriage return
	\t 	horizontal tab
	\v	vertical tab
	\\	backslash
	\? 	question mark
	\'	single quote
	\"	double quote
	\ooo	octal number
	\xhh	hexadecimal number

*/

int main(){

	/* \r use to switch to newline. this is not use in linux, but will use in windows os. */
	printf("\r\n");
	printf("\n");

	/* \f use to move to next page. */
	printf("hello");
	printf("\f");
	printf("smile");

	return 0;

}
