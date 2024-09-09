#ifndef _TEAM_
#define _TEAM_
#define CODE_LEN  3

#include "Coach.h"
#include "Swimmer.h"

typedef enum {
	eName,
	eAge,
	eSwimmerNofSortOpt
} eSwimmerSortOption;


typedef struct 
{
	char* country;
	char countryCode[CODE_LEN + 1];
	Swimmer** teamSwimmerArr;
	int capacity;
	int swimmersCount;
	int numOfMedals;
	char* cheeringChants;
	int numOfChampionship;
	int numOfWorldRecord;
	Coach* teamCoach;
}Team;


Team*	initTeamToCompetition();
int		initTeam(Team* team, char* country, char* countryCode);
char*	getCountryName(Team* team);
void	getCountryCode(char* code);
void	printTeamSwimmers(const Team* team);
int		addCoach(Team* team, Coach* coach);
void	freeTeam(Team* team,int count);
void	freeTeamSwimmers(Team* team);
void	printTeam(const Team* team);
int		setCoachToTeam(Team* team, Coach* coach);
void	printSwimmerArrToTeam(const Swimmer** swimmers, int count);




#endif