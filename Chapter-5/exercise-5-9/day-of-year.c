#include "stdio.h"

/**

	this will help to calculate the day of the year.

*/

static int daytab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};
	

int day_of_year(const int year, const int month, int day){
		

	if(year < 1970){
		printf("the year is inlegal!\n");
		return -1;
	}

	if(month > 12){
		printf("the month is larger than 12!\n");
		return -1;
	}

	if(day > 31){
		printf("the month day is out of range!\n");
		return -1;
	}

	int index;
	int leap;

	leap = (year%4 && year%100 != 0) || year%400 == 0;
	// check 
	if(day > daytab[leap][month]){
		printf("the day in month %d is out of range, please check.\n", month);
		return -1;
	}

	for(index=1; index < month; index++){
		day += *(*(daytab+leap)+index);
	}
	
	return day;
}	

void month_day(int year, int yearday, int *pmonth, int *pday){

	int index;
	int leap;

	leap = (year%4 && year%100 != 0) || year%400 == 0;
	// check
	if((yearday > 365 && leap == 0) || (yearday > 365 && leap == 1)){
		printf("the year do not contains these days!\n");
		return (void)0;
	}

	for(index=1; yearday>daytab[leap][index]; index++){
		yearday -= *(*(daytab+leap)+index);
	}	

	*pmonth = index;
	*pday = yearday;

}

int main(void){

	int month, day;

	printf("year: %d, month: %d, day: %d, and is %d day of the year.\n", 2005, 5, 24, day_of_year(2005, 5, 24)); 

	month_day(2030, 234, &month, &day);
	printf("the %d day is the day %d, month %d of year %d.\n", 234, day, month, 2030);

	printf("year: %d, month: %d, day: %d, and is %d day of the year.\n", 2025, 4, 31, day_of_year(2025, 4, 31)); 
	
	return 0;
}
