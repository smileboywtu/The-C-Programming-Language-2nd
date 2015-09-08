#ifndef __FUNC__
#define __FUNC__

#include "stdio.h"
#include "ctype.h"
#include "string.h"
#include "stdlib.h"

#define LINE_LIMIT	1024
#define LINE_NUMBER	100
#define FREE_SPACE	(LINE_LIMIT*LINE_NUMBER)

typedef int (*compare)(char*, char*); 

char* memalloc(int size);
void 	memfree(char* p);

int 	getnewline(char* line, const int limit);

int cmpstr(char*, char*);
int cmpnumber(char*, char*);

void quicksort(char* array[], const int low, const int high);

#endif
