#include "stdio.h"


/**

	you may ever know the cool program like this.

*/

void squeeze(char *str, char c){

	int i, j;

	for(i=j=0; str[i] != '\0'; i++){

		if(str[i] != c){
			str[j++] = str[i];
		}

	}

	str[j] = '\0';

}


int main(){

	char str[] = "Hepppppppppppppppppppppppppppllo, smile";

	printf("get the p out of %s\n", str);

	squeeze(str, 'p');

	printf("%s\n", str);

	return 0;
}
