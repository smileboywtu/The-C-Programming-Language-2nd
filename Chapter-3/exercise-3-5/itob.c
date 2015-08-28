#include "stdio.h"

/**

	convert an integer into string base on b.

*/

void reverse(char* str, int high){

	int index;
	char temp;
	for(index=0; index < high - index; index++){
		temp = str[index];
		str[index] = str[high - index];
		str[high - index] = temp;
	}
}

void itob(int n, char* str, const char base){

	char mod;
	int index;
	char sign, flag;

	if(n < 0){
		sign = -1;
		n = -n;
	}

	flag = 0;
	index = 0;
	
	/* fill the sequence base on base. */
	do{

		if(flag){	n += 1; }	
		mod = n < 0 ? n = -(n + 1), (base == n % base + 1? flag = 1, 0 : n % base) : n % base;
		str[index++] = mod >= 10 ? mod - 10 + 'A' : mod + '0';

	}while( (n/=base) > 0);

	/* fill the header. */
	if(8 == base){
		str[index++] = '0';
	}else if(16 == base){
		str[index++] = 'x';
		str[index++] = '0';
	}

	/* fill the sign. */
	if(0 > sign){
		str[index++] = '-';
	}

	/* fill the tail. */
	str[index] = '\0';

	reverse(str, index-1);
}


int main(){

	int value;
	char str[128];

	value = 30;

	printf("the source value base on 10 is: %d.\n", value);

	itob(value, str, 2);
	printf("base on 2, the str is: %s\n", str);

	itob(value, str, 8);
	printf("base on 8, the str is: %s\n", str);

	itob(value, str, 16);
	printf("base on 16, the str is: %s\n", str);

	return 0;
}
