#include "stdio.h"
#include "time.h"

/**

	binary search.

*/

#define MAX_ARRAY_ELEM	300

typedef int (*pf)(int, int*, int);

/* calculate the time. */
unsigned long gettimes(pf p){
	
	int i;
	int x, n;
	int v[MAX_ARRAY_ELEM];
	clock_t time_taken;

	x = -1;
	n = MAX_ARRAY_ELEM;

	for(i=0; i<MAX_ARRAY_ELEM; i++){
		v[i] = i;
	}

	for(i=0,time_taken=clock(); i<100000; i++){
		(*p)(x, v, n);
	}
	
	time_taken = clock() - time_taken;

	return time_taken;
}	

/* just for test. */
int printhello(int x, int v[], int n){
		
	printf("hello, world.\n");

	return -1;
}

/* traditional way. */
int binsearch(int x, int v[], int n){

	int low, mid, high;

	low = 0;
	high = n-1;
	while(low<=high){
		mid = (low+high)/2;
		if(x < v[mid]){
			high = mid -1;
		}else if(x > v[mid]){
			low = mid + 1;
		}else{
			return mid;
		}
	}
	
	return -1;
}

/* only one test inside the loop. */
int binsearch1(int x, int v[], int n){

	int low, mid, high;

	low = 0;
	high = n -1;
	mid = (low+high)/2;
	while(low < high && x != v[mid]){
		if(x < v[mid]){
			high = mid - 1;
		}else{
			low = mid + 1;
		}
		mid = (low+high)/2;
	}
	if(x == v[mid]){
		return mid;
	}

	return -1;
}

/* third way to do this. */
int binsearch2(int x, int v[], int n){
	
	int low, mid, high;

	low = 0;
	high = n-1;
	
	while(low <= high){

		mid = (low+high)/2;
		if(x == v[mid]){
			return mid;
		}
		low = x > v[mid]? mid+1 : low;
		high = x > v[mid]? high : mid - 1;
	}

	return -1;
} 

		
int main(){
	
	pf f;
	// test binsearch
	f = binsearch;
	printf("time taken using binsearch: %lu.\n", gettimes(f));
	// test binsearch1
	f = binsearch1;
	printf("time taken using binsearch1: %lu.\n", gettimes(f));
	// test binsearch2
	f = binsearch2;
	printf("time taken using binsearch2: %lu.\n", gettimes(f));
//	f = &printhello;
//	(*f)(1, NULL, 5);
	return 0;
}
