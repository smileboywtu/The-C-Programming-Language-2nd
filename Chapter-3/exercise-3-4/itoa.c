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

void itoa(int n, char* s){

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
	s[i] = '\0';
	// reverse the string
	reverse(s, i-1);
}

int main(){
	
	int  i = 0x80000001;
	char number[BUFFER_SIZE];

	itoa(i, number);

	printf("the number is: %s\n", number);

	return 0;

}
