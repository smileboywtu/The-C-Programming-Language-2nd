

/**

	this program sort the array of string.

*/
	
#define SWAP(t, a, b)	\
{											\
	t tempvalue;				\
	tempvalue = a;			\
	a = b;							\
	b = tempvalue;			\
}											\

char strcmpignorecase(const char* str1, const char* str2);

int partition(char* v[], const int low, const int high){
	// set the pivot
	char* pivotstr = v[high];

	int cursor;
	int index;
	for(cursor=0, index=0; cursor<high; cursor++){
		if(strcmpignorecase(v[cursor], pivotstr)<0){
			// this mean the sort the string in order of alpha order.
			SWAP(char*, v[cursor], v[index])
			index++;
		}	
	}
	// fill the proper position
	SWAP(char*, v[index], v[high])
	
	return index; 
}

void quicksort(char* v[], const int low, const int high){
	
	int part;
	
	if(low < high){
		
		part = 	partition(v, low, high);
		quicksort(v, low, part-1);
		quicksort(v, part+1, high);	
	}
}

