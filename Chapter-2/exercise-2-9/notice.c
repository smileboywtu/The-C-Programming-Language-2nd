#include "stdio.h"

/**

	expr1 op = expr2 is equivalent to expr1 = (exp1) op (expr2).

*/

int main(){

	int a, b;

	a = 30;
	b = 3;

	a *= b + 2;

	printf("a is %d.\n",a);

	return 0;
}
