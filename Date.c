#include "Date.h"
#include<stdio.h>



void initDate(Date* date, int day, int month, int year) 
{
    if (date == NULL)
    {
        return;
    }
    date->day = day;
    date->month = month;
    date->year = year;
}


void printDate(const Date* date) 
{
    if (date == NULL)
    {
        printf("No date available.\n");
        return;
    }

    printf("The date is : %02d/%02d/%04d\n", date->day, date->month, date->year);
}

int isLeapYear(int year) 
{
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

int checkDate(Date* date) 
{
    if (date == NULL) 
    {
        return 0; 
    }
    if (date->year < 0 || date->month < 1 || date->month > 12) 
    {
        return 0; 
    }
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear(date->year)) 
    {
        daysInMonth[1] = 29; 
    }
    if (date->day < 1 || date->day > daysInMonth[date->month - 1]) 
    {
        return 0; 
    }
    return 1; 
}
void getDateInput(Date* dateInput) 
{
    if (dateInput == NULL)
        return;
    do 
    {
        printf("Enter competition date (day/month/year): ");
        scanf("%d/%d/%d", &dateInput->day, &dateInput->month, &dateInput->year);
        if (!checkDate(dateInput)) 
        {
            printf("Invalid date. Please try again.\n");
        }
    } while (!checkDate(dateInput));
}

