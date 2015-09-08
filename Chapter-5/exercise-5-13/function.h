#ifndef __FUNC__
#define __FUNC__

#include "stdio.h"

#define LINE_LIMIT	1024
#define LINE_NUMBER	100
#define FREE_SPACE	(LINE_LIMIT*LINE_NUMBER)

char* memalloc(int size);
void 	memfree(char* p);
int 	getnewline(char* line, const int limit);

#endif
