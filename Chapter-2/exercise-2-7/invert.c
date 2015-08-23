#include "stdio.h"
#include "stdlib.h"

/**

	invert the n bits begin at p in x.
	0000_11_00
	^
	0000_11_00
	=
	0000_00_00
*/
#define BIT_BUFFER_SIZE	64

/*  get the bit string. */
char* getbitstr(unsigned x){
	
	int cursor;
	int length;
	char *bits;

	bits = (char*)malloc(BIT_BUFFER_SIZE);	

	length = sizeof(x)*8-1;
	for(cursor=0; cursor<=length; cursor++){

		if(x & (1<<(length-cursor))){
			bits[cursor] = '1';
		}else{
			bits[cursor] = '0';
		}
	}

	bits[cursor] = '\0';

	return bits;
}

/* invert n bits begin at p in x. */
unsigned invert(unsigned x, int p, int n){
	return x ^ (~0<<(p+1-n) ^ (~0<<(p+1)));
}

int main(){

	unsigned int a, b;
	char* p, *q, *r, *s;

	a = 0x55;
	b = 0x00;
	p = getbitstr(a);
	q = getbitstr(~0);
	r = getbitstr(a^b);
	s = getbitstr(invert(a, 4, 2));

	printf("the ~0 is: %d\n", ~0);
	printf("the bit string of ~0 is %s.\n", q);
	printf("the bit string of a is %s.\n", p);
	// test
	printf("a ^ b is %s\n", r);
	printf("invert(a, 4, 2) is: %s.\n", s);

	free((char*)p);
	free((char*)q);
	free((char*)r);
	free((char*)s);
	p = NULL;
	q = NULL;
	r = NULL;
	s = NULL;
	return 0;
}
	
