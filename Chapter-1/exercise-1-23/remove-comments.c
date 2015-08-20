#include "stdio.h"
#include "comments.h"

/**

	this program to help remove the comments in the c source file.

	In C Language:
		// this is a comment.
		// /\*	this is a comment too. *\/
*/


int main(){

	short cur;

	while(EOF != (cur=getchar())){
		if(isInComments(cur)){
			if('\n' == cur || '\t' == cur){
				putchar(cur);
			}else{
				putchar(' ');
			}
		}
		else{
			putchar(cur);
		}	
	}

	// for test quote
	printf("Test: // this is not a comment.");
	printf("Test: /* not a comment too.*/");

	

	return 0;
}
		
	
