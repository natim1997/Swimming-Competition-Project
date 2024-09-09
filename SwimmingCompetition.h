#ifndef _SWIMMINGCOMPETITION_
#define _SWIMMINGCOMPETITION_

#include "Address.h"
#include "Date.h"
#include "SwimmingEvent.h"

typedef enum {
	eNumOfChampionships,
	eNumOfWorldRecords,
	eCountry,
	eTeamNofSortOpt
} eTeamSortOption;

typedef struct 
{
	Team* teamArr;
	int numOfTeams;
	char* competitionName;
	Address* address;
	Date* date;
	SwimmingEvent* eventArr;
	int countEvent;
}SwimmingCompetition;

void	getCompetition(SwimmingCompetition* competition);
int		isSameCompetition(SwimmingCompetition* comp1, SwimmingCompetition* comp2);
void	freeCompetition(SwimmingCompetition* competition);
void	printCompetition(SwimmingCompetition* competition);
void	printEvents(SwimmingEvent* events, int count);
int		compareTeamByChampionships(const void* a, const void* b);
int		compareTeamByWorldRecords(const void* a, const void* b);
int		compareTeamByCountry(const void* a, const void* b);
eTeamSortOption showTeamSortMenu();
void	sortTeams(Team* teams, int teamCount);
void	findTeam(const Team* teams, int teamCount);
void	freeEventArr(SwimmingCompetition* competition);
void	freeTeamArr(SwimmingCompetition* competition);
void	getCode(char* code);
void	addTeamToCompetition(SwimmingCompetition* competition, Team* newTeam);
int		isTeamAvailable(SwimmingCompetition* competition);
void	showTeamList(const Team* teams, int teamCount);
void	addHeatToEvent(SwimmingCompetition* competition, SwimmingEvent* event);
void	addSwimmersToHeat(SwimmingCompetition* competition, SwimmingHeat* heat);
int		isSwimmerInOtherHeats(SwimmingCompetition* competition, Swimmer* swimmer, int currentHeatIndex);
void	simulateAndSortHeat(SwimmingCompetition* competition, SwimmingEvent* event, SwimmingHeat* heat);
Team*	findSwimmerTeam(SwimmingCompetition* competition, Swimmer* swimmer);
void	awardYoungestSwimmer(SwimmingCompetition* competition);



#endif