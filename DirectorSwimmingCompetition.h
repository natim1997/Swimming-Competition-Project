#ifndef _DIRECTORSWIMMINGCOMPETITION_
#define _DIRECTORSWIMMINGCOMPETITION_

#include "SwimmingCompetition.h"
#include "List.h"
#include"Address.h"
#include"Date.h"

typedef struct
{
	LIST SwimmingCompetitonList;
	int countCompetition;
}DirectorSwimmingCompetition;

DirectorSwimmingCompetition* initDirector();
SwimmingCompetition* chooseCompetition(DirectorSwimmingCompetition* director);
SwimmingCompetition* initCompetition();
int		addSwimmingCompetition(DirectorSwimmingCompetition* director);
int		initSwimmingCompetition(SwimmingCompetition* competition, const char* name, const char* country, Address* address, Date* date);
void	freeDirector(DirectorSwimmingCompetition* director);
void	printCompetitionArr(const DirectorSwimmingCompetition* director);
int		isDataAvailable(const DirectorSwimmingCompetition* director);
void	addTeam(DirectorSwimmingCompetition* director);
void	addSwimmerToTeam(DirectorSwimmingCompetition* director);
void	addSwimmerToTeamArray(Team* team, Swimmer* newSwimmer);
void	addEventToCompetition(DirectorSwimmingCompetition* director);
void	addEventToCompetitionArray(SwimmingCompetition* competition, SwimmingEvent* newEvent);
char*	getUniqueCountryName(SwimmingCompetition* selectedCompetition);
char*	getUniqueCountryCode(SwimmingCompetition* selectedCompetition);
Coach*	createUniqueCoach(SwimmingCompetition* selectedCompetition);



#endif