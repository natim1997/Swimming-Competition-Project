#ifndef _COACH_
#define _COACH_
//#include "Team.h"


typedef struct 
{
	char* name;
	int age;
	int experience;
	char* country;
	int numOfChamps;
}Coach;

int		initCoach(Coach* coach,char* name,int age);
void	printCoach(Coach* coach);
void	freeCoach(Coach* coach);


#endif