#include "stdio.h"

/**

	remove each character in s1 that matches any character in s2.
	here just use the hashmap, because when the string is very long it may cause
	many memory, so this way, it works faster.

*/

#define HASH_DIVIDER	14

void squeeze(char* str1, char* str2){

	char c;
	int cursor, preserve;		
	char hashmap[HASH_DIVIDER][HASH_DIVIDER] = {{0}};

	for(cursor=0; (c=str2[cursor]) != '\0'; cursor++){
		hashmap[c/HASH_DIVIDER][c%HASH_DIVIDER] = 1;
	}	

	for(cursor=0, preserve=0; (c=str1[cursor]) != '\0'; cursor++){
		if(0 == hashmap[c/HASH_DIVIDER][c%HASH_DIVIDER]){
			str1[preserve++] = c;
		}
	}

	str1[preserve] = '\0';
}


int main(){

	char str1[] = "hello, smileboy";
	char str2[] = "elb";

	// show source
	printf("the default str1 is: %s\n", str1);
	printf("the default str2 is: %s\n", str2);

	squeeze(str1, str2);

	printf("after squeeze, str1 is: %s\n", str1);


	return 0;

}
