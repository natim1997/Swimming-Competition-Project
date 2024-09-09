#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Coach.h"


int initCoach(Coach* coach,char* name,int age)
{
    if (coach == NULL)
        return 0;
 
    coach->name = _strdup(name);
    coach->country = NULL;
    
    if (coach->name == NULL)
    {
        freeCoach(coach);
        return 0;
    }
    coach->age = age;
    coach->experience = 0;
    coach->numOfChamps = 0;
    return 1;
}

void printCoach(Coach* coach)
{
    if (coach == NULL)
    {
        printf("No coach data available.\n");
        return;
    }
    printf("------------------\n");
    printf("Coach Name : %s\nAge : %d\nExperience : %d years\nCountry : %s\nChampionships : %d\n",
        coach->name, coach->age, coach->experience, coach->country, coach->numOfChamps);
}

void freeCoach(Coach* coach)
{
    if (coach != NULL)
    {
        free(coach->name);
        free(coach->country);
    }
}