#include "stdio.h"

/**

	use the recursive code to deal with itoa.

*/

void reverse(char* str, int index){

	static char reset;
	static int indexofhigh;

	short temp;
	
	if(reset == 0){
		indexofhigh = index;
		reset = !reset;
	}
	
	if(index > indexofhigh-index){
		// swap
		temp = str[index];
		str[index] = str[indexofhigh-index];
		str[indexofhigh-index] = temp;
		// recursion
		reverse(str, index-1);
	}else{
		reset = 0;	
	}
}

void itoa(char* str, const int base, int n){

	static int index;
	static char sign;

	int mod;

	// make the number positive
	if(n < 0){
		sign  = -1;
		n = -n;
	}

	// get the char
	if(n < 0 && sign == -1){

		n = -(n + 1);
		mod = n % base;
		str[index++] = (mod+1 == base ? n+=base, '0' : (mod >= 10? mod-10+'A' : mod+'0')); 	
		itoa(str, base, n / base);

	}else if(n == 0){
		
		if(base == 8){
			str[index++] = '0';
		}else if(base == 16){
			str[index++] = 'X';
			str[index++] = '0';
		}

		if(sign == -1){
			str[index++] = '-';
		}
		// close the string
		str[index] = '\0';
		// reverse
		reverse(str, index-1);

		// here you need to reset the index manually
		index = 0;
		sign = 0;

	}else{
		
		mod = n % base;
		str[index++] = mod >= 10? mod - 10 + 'A' : mod + '0';
		itoa(str, base, n / base);

	}
	
}



int main(void){


	int a;
	char str[256];

	a = 34;

	itoa(str, 8, a);

	printf("the string of %d is %s base on 8.\n", a, str);

	itoa(str, 16, a);

	printf("the string of %d is %s base on 16.\n", a, str);

	return 0;
}
