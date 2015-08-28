#include "stdio.h"
#include "ctype.h"

/**

	expand the shorthand notation.

*/

#define SH_0	0
#define SH_1	1
#define SH_2	2

#define BUFFER_SIZE	256

void expand(const char* str1, char* str2);

int main(){

	char str1[] = "a-z is the alpha character, 0-9 is the digit number.";
	char str2[] = "a-b-c is an expression, -a-z will be expand, a- is not legel in c language.";
	char str3[] = "a-Z will not expand.";
	char str4[BUFFER_SIZE];

	printf("str1: %s\n", str1);

	// test str1
	expand(str1, str4);

	printf("string expanded from str1 is: %s\n", str4);

	putchar('\n');

	printf("str2: %s\n", str2);
	// test str2
	expand(str2, str4);

	printf("string expanded from str2 is: %s\n", str4);

	putchar('\n');

	printf("str3: %s\n", str3);
	// test str3
	expand(str3, str4);

	printf("string expanded from str3 is: %s\n", str4);

	return 0;
}


/*	expand shorthand in s1 into s2. */
void expand(const char* str1, char* str2){

	int i, j;
	char c, pre;
	char state;

	j = 0;
	state = SH_0;	
	for(i=0; (c=str1[i]) != '\0'; i++){
			
		if(state == SH_0 && (isdigit(c) || isalpha(c))){
			state = SH_1;
			pre = c;
		}

		else if(state == SH_1 && c == '-'){
			state = SH_2;
		}

		else if(state == SH_2 && (isdigit(pre)&isdigit(c) || (islower(pre)&islower(c) && isalpha(pre)&isalpha(c)))){
			// expand short hand
			if(pre == c || pre == c-1 || pre == c+1){
				str2[j++] = pre, str2[j++] = '-', str2[j++] = c;
			}else{
				while(pre != c){
					str2[j++] = pre < c? pre++ : pre--;	
				}
				str2[j++] = pre;
			}
			// reset the state
			state = SH_0;
		}

		else{
			switch(state){
				case SH_0:
					{	str2[j++] = c; break;}
				case SH_1:
					{ str2[j++] = pre, str2[j++] = c; break;}
				case SH_2:
					{	str2[j++] = pre, str2[j++] = '-', str2[j++] = c; break;}
				default:
					{ break;}
			}
			state = SH_0;
		}	// end else
	}	// end for

	str2[j] = '\0';
}

