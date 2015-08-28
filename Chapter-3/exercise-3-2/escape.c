#include "stdio.h"

/**

	make the escape character visiable or invisiable.

*/

void escapev(char* str, const char* from){
	
	int cursor, saver;
	short c;

	cursor = 0;
	saver = 0;
	while((c=from[cursor]) != '\0'){
		switch(c){
			case '\b':
				{str[saver++] = '\\'; str[saver++] = 'b'; break;}
			case '\t':
				{str[saver++] = '\\'; str[saver++] = 't'; break;}
			case '\n':
				{str[saver++] = '\\'; str[saver++] = 'n'; break;}
			default:
				{str[saver++] = c; break;}
		}
		cursor++;
	}	

	str[saver] = '\0';

}

/* make the character invisiable. */
void escapei(char* str, const char* from){

	int cursor, saver;
	short c;
	char flag = 0;

	cursor = 0;
	saver = 0;
	while((c=from[cursor]) != '\0'){
		switch(c){
			case '\\':
				{	
					if(1 == flag){
						str[saver++] = '\\';
					}else{						
						flag = 1;
					}
					break;
				}
			case 'b':
				{ str[saver++] = 1 == flag? '\b' : 'b'; flag = 0; break;}	
			case 'n':
				{ str[saver++] = 1 == flag? '\n' : 'n'; flag = 0; break;}
			case 't':
				{ str[saver++] = 1 == flag? '\t' : 't'; flag = 0; break;}
			default:
				{	
					if(1 == flag){
						str[saver++] = '\\';
						flag = 0;
					}
					str[saver++] = c;
					break;
				}
		}
		cursor++;
	}

	str[saver] = '\0';

}


int main(){

	char from[] = "hello,\tmom.\n";
	char s[50];

	printf("the source string is: %s", from);
	escapev(s, from);
	printf("using escapev, the string is %s", s);
	putchar('\n');
	escapei(from, s);
	printf("using escapei, the string is %s", from);	

	return 0;
}
