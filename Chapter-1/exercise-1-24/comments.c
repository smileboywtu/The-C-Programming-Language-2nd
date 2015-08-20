#include "comments.h"

static char initflag = 0;

// local
void markquote();
void recordState(short cur);

// header
void init(){

	extern char commentstate;
	extern char quotestate;
	extern char reservestate;

	commentstate = COMMENT_OUT;
	quotestate = QUOTE_OUT;
	reservestate = commentstate;
}

char isInQuote(){

	extern char quotestate;

	return quotestate;
}

char isInComments(short cur){

	extern char commentstate;
	extern char reservestate;
	
	if(0 == initflag){
		init();
		initflag = 1;
	}

	// logical here
	recordState(cur);

	// retrun
	if(COMMENT_OUT == commentstate && COMMENT_OUT == reservestate){
		return 0;
	}

	return 1;
}

/*************************************************************

			LOCAL FUNC

*************************************************************/
void recordState(short cur){

	extern char commentstate;
	extern char reservestate;

	reservestate = commentstate;

	if('"' == cur){
		markquote();
	}

	else if('/' == cur){
		if(QUOTE_OUT == isInQuote()){
			if(COMMENT_OUT == commentstate){	commentstate = COMMENT_START; }
			else if(COMMENT_START == commentstate){ commentstate = COMMENT_IN_SINGLE; }
			else if(COMMENT_STOP == commentstate){	commentstate = COMMENT_OUT; }
		}
	}

	else if('*' == cur){
		if(QUOTE_OUT == isInQuote()){
			if(COMMENT_IN_MULTI == commentstate){	commentstate = COMMENT_STOP;	}
			else if(COMMENT_START == commentstate){	commentstate = COMMENT_IN_MULTI;	}
		}
	}

	else if('\n' == cur){
		if(QUOTE_OUT == isInQuote()){
			if(COMMENT_IN_SINGLE == commentstate){	commentstate = COMMENT_OUT; }
		}
	}

	/* must check every time */
	if(COMMENT_STOP == commentstate && '*' != cur){
		commentstate = COMMENT_IN_MULTI;
	}
}


void markquote(){

	extern char commentstate;
	extern char quotestate;

	if(COMMENT_OUT == commentstate){
		if(QUOTE_OUT == quotestate){
			quotestate = QUOTE_IN;
		}else{
			quotestate = QUOTE_OUT;
		}
	}
}
