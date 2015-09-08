#include "func.h"
#include "stdio.h"
#include "ctype.h"
#include "string.h"

/** 

	this is the implemention of the gettype.

*/

char checknumber(const char* str);

int gettype(const char* str){

	if(isalpha(*str)){
		if(strcasecmp(str, "SIN")){	return SIN;}
		else if(strcasecmp(str, "COS")){	return COS;}
		else if(strcasecmp(str, "POWER")){	return POWER;}
		else if(strcasecmp(str, "EXP")){	return EXP;}
		else{	printf("illegal operator.\n"); return -1;}
	}else if(strlen(str) == 1 && (*str == '+' || *str == '-' || *str == '*' || *str == '/')){
		return *str;
	}else{
		if(checknumber(str)){
			return NUMBER;	
		}
	}

	return -1;
}

char checknumber(const char* str){
	
	short c;
	while((c=*str++)){
		if(!isdigit(c) && c != '+' && c != '-' && c != '.'){
			return 0;
		}
	}
	return 1;
}
