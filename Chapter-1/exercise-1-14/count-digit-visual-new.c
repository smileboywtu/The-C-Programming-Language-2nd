#include "stdio.h"

/**

	use the array to save the result.
	keep care that you can just use the number of horizen <= 99, which means you can just define HISTOGRAM <= 99.

*/
#define HISTOGRAM		20	
#define X_ASIX_MAX	HISTOGRAM	
#define Y_ASIX_MAX	50
#define NUMBER_MAX	50000.0

void showVerticalHistogram(int nArray[], int len, int xAsix, int yAsix){
	if(0 == xAsix){
		xAsix = X_ASIX_MAX;
	}

	if(0 == yAsix){
		yAsix = Y_ASIX_MAX;
	}

	int i, j;
	int size;
	int percentCount[HISTOGRAM];

	size = len;
	for(i=0; i < HISTOGRAM && i < size; i++){
		percentCount[i] = nArray[i]/NUMBER_MAX*Y_ASIX_MAX;
		if(50 < percentCount[i]){
			percentCount[i] = 50;
		}
	}

	/**
		for the test use.		
	printf("percent = ");
	for(i=0; i<10; i++)
		printf(" %d",percentCount[i]);
	putchar('\n');
	*/

	for(i=Y_ASIX_MAX+2; i>0; i--){

		if(i > 2){
			printf("%3d |  ", i-2);
		}else if(2 == i){
			printf("%3d +--", i-2);
		}else{
			printf("       ");
		}

		for(j=0; j<size; j++){
			if(i-2 <= percentCount[j] && i > 2){
				putchar('*');
			}else{
				if(2 == i){
					putchar('-');								
				}else if(1 == i){
					if(0 <= j && j <= 9){
						putchar(j+'0');	
					}else{
						putchar(j/10+'0');
						putchar(j%10+'0');		
					}
				}else{	
					putchar(' ');
				}
			}
			if(2 == i){
				putchar('-');	
				putchar('-');	
			}else{
				putchar(' ');
				putchar(' ');
			}
		} // end for-inside
		putchar('\n');
	} // end for-outside
	
}

int main(){

	short c;

	int whitespaces, others;
	int digits[12];

	int i;

	whitespaces = 0;
	others = 0;
	
	for(i=0; i<10; i++)
		digits[i] = 0;
	
	while(EOF != (c = getchar())){
		if(c >= '0' && c <= '9'){
			++digits[c-'0'];
		}else if(' ' == c || '\n' == c || '\t' == c){
			++whitespaces;
		}else{
			++others;
		}
	}

	printf("Digits = ");
	for(i=0; i<10; i++)
		printf(" %d",digits[i]);
	printf(", white space = %d, other = %d\n", whitespaces, others);

	digits[10] = whitespaces;
	digits[11] = others;

	showVerticalHistogram(digits,12, 0, 0);	
	
	return 0;
}
