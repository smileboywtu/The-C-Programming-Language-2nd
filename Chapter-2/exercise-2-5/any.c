#include "stdio.h"

/**

	return the first location where a charater from s2 and also in s1.
*/

#define HASH_DIVIDER	14

int any(char* str1, char* str2){

	char c;
	int cursor;		
	char hashmap[HASH_DIVIDER][HASH_DIVIDER] = {{0}};

	for(cursor=0; (c=str2[cursor]) != '\0'; cursor++){
		hashmap[c/HASH_DIVIDER][c%HASH_DIVIDER] = 1;
	}	

	for(cursor=0; (c=str1[cursor]) != '\0'; cursor++){
		if(1 == hashmap[c/HASH_DIVIDER][c%HASH_DIVIDER]){
			return cursor;
		}
	}

	return -1;
}


int main(){

	char str1[] = "hello, smileboy";
	char str2[] = "elb";
	char str3[] = "2";

	// show source
	printf("the default str1 is: %s\n", str1);
	printf("the default str2 is: %s\n", str2);
	printf("the default str3 is: %s\n", str3);

	printf("after any, first location in str1 as str2 is: %d\n", any(str1, str2));
	printf("after any, first location in str1 as str3 is: %d\n", any(str1, str3));

	return 0;

}
