#include "stdio.h"
#include "stdlib.h"

/**

	return x with the n bits that begin at position p set to the rightmost n bits of y, leaving other bits unchanged.
	first make the x positon is zero and then get the part from y, then or them.

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

/*	set the n bits of x start at p with the n bits rightmost in y. */
unsigned setbits(unsigned x, int p, int n, unsigned y){
	return (x & ~(~(~0 << n) << (p+1-n))) | (( y & ~(~0<<n)) << (p+1-n)); 	
}

int main(){

	unsigned int a, b;
	char* p, *q, *r, *s;

	a = 0xFF;
	b = 0x00;
	p = getbitstr(a);
	q = getbitstr(~0);
	r = getbitstr(b);

	printf("the ~0 is: %d\n", ~0);
	printf("the bit string of ~0 is %s.\n", q);
	printf("the bit string of a is %s.\n", p);
	// test
	printf("the bit string of b is %s.\n", r); 
	s = getbitstr(setbits(a, 6, 3, b));	
	printf("after setbits(a, 6, 3, b), bit string of a is: %s.\n", s);

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
	
