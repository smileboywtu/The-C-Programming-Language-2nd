#include "stdio.h"

/**

	make the string to lower case.

*/

int lower(int c);
void tolowercase(char *str);

int main(){

	char str[] = "hELlo";
	char *p = "hELlo";

	tolowercase(str);

	printf("%s\n", str);
	printf("%s\n", p);


	return 0;
}

/* get the lower one. */
int lower(int c){

	if(c >= 'A' && c <= 'Z'){
		return c + 'a' - 'A';
	}else{
		return c;
	}
}

/* to lower case. */
void tolowercase(char *str){

	int c;
	int cur;

	for(cur=0; (c=str[cur]) != '\0'; cur++){
	
		str[cur] = lower(c);
	}

}	
		
