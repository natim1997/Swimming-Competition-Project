#ifndef _DATE_
#define _DATE_


typedef struct
{
	int day;
	int month;
	int year;
}Date;

int		isLeapYear(int year);
int		checkDate(Date* date);
void	printDate(const Date* date);
void	initDate(Date* date, int day, int month, int year);
void	getDateInput(Date* dateInput);
#endif
