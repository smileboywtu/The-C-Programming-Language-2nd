#include "stdio.h"

/**

	shell sort.

*/

void shellsort(int v[], int n){

	int i, j, t;
	int gap;
	int temp;

	for(gap=n/2; gap>0; gap/=2){
		for(i=gap; i<n; i++){
			temp = v[i];
			for(j=i; (j>=gap) && (v[j-gap] > temp); j-=gap){
				v[j] = v[j-gap];
			}
			v[j] = temp;
		}							
		//test
		printf("the current gap is: %d\n", gap);
		for(t=0; t<n; t++){
			printf(" %d", v[t]);	
		}	
		putchar('\n');
	}

}


int main(){

	int a[] = {
		1, 34, 23, 56, 87, 2, 67, 45, 5, 21};

	int i;
	int n;

	n = 10;

	shellsort(a, n);
	for(i=0; i<n; i++){
		printf(" %d", a[i]);
	}
	putchar('\n');

	return 0;

}
