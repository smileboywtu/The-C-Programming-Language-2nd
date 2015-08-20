#include "stdio.h"

/**
	
	default return type for function.
	but you will get a warning when compile.

*/

print(char str[]){
	
	printf("%s\n", str);
	
	return 0;
}

main(){

	putchar('H');
	putchar('e');
	putchar('l');
	putchar('l');
	putchar('o');

	putchar('\n');
	
	print("world.");

	return 0;
}
