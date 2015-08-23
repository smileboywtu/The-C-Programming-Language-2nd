#include "stdio.h"
#include "ctype.h"

/**

	convert a string of hex to integer.

*/

int htoi(const char* str){
	
	int c;
	int cur, result;

	const char HEX[] = {10, 11, 12, 13, 14, 15};
	
	cur = 0;
	if(str[cur] == '0' && (str[cur+1] == 'x' || str[cur+1] == 'X')){
		cur += 2;
	}

	result = 0;
	while((c=str[cur]) != '\0'){
		if(isdigit(c)){
			result = 16*result + c-'0';
		}else if(isxdigit(c)){
			result = 16*result + HEX[tolower(c) - 'a'];
		}else{
			break;
		}	
		cur++;
	}

	return result; 

}


int main(){

	int n;
	char str[] = "0x1f";

	n = htoi(str);

	printf("hex string %s is value of %d. \n", str, n);

	return 0;

}
