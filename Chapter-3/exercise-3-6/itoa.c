#include "stdio.h"

/**

	this program convert the integer to string.

*/

#define BUFFER_SIZE 1024

void reverse(char* s, int n){
	
	int i;
	char temp;
	for(i=0; i<n-i; i++){
		temp = s[i];
		s[i] = s[n-i];	
		s[n-i] = temp;
	}	
}

void itoa(int n, char* s, const int wide){

	int i, sign;

	if( (sign = n) < 0){
		n = -n;
	}

	i = 0;
	do{
		s[i++] = n < 0? n=-(n+1), n%10 + '1': n%10 + '0';
	}while((n/=10) > 0);

	if(sign < 0){
		s[i++] = '-';
	}

	/* fill the blank. */
	while(i < wide){
		s[i++] = ' ';
	}
	
	/* fill tail. */
	s[i] = '\0';

	// reverse the string
	reverse(s, i-1);
}

int main(){
	
	int  i = 34;
	char number[BUFFER_SIZE];

	itoa(i, number, 10);

	printf("the number is: %s\n", number);

	i = 345;
	itoa(i, number, 10);

	printf("the number is: %s\n", number);

	i = 123456789;
	itoa(i, number, 10);

	printf("the number is: %s\n", number);

	return 0;

}
