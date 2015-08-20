#ifndef __COMMENT__H__
#define __COMMENT__H__

#define COMMENT_OUT				0
#define COMMENT_START			1
#define COMMENT_IN_SINGLE	2
#define COMMENT_IN_MULTI	3
#define COMMENT_STOP			4


#define QUOTE_IN			6
#define QUOTE_OUT			7

char quotestate, commentstate, reservestate;

char isInComments(short cur);
char isInQuotes();
void init();




#endif
