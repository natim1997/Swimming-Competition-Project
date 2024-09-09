#pragma once
#include "DirectorSwimmingCompetition.h"
#include "DirectorSwimmingCompetitionFile.h"
#include "SwimmingCompetition.h"
#include"Team.h"


#define COMPETITION_BINARYFILE "swimmingCompetition.bin"
#define COMPETITION_TEXTFILE "SwimmingCompetition.txt"

void	printMenu();
void	loadSystemFromFile(DirectorSwimmingCompetition* director, SwimmingCompetition* pComp);
void	displaySystem(const DirectorSwimmingCompetition* director);
void	displaySubcomponents(const DirectorSwimmingCompetition* director);
void	printAddComponentMenu();
void	addComponent(DirectorSwimmingCompetition* director);
void	sortComponents(SwimmingCompetition* competition);
void	PrintSortMenu();
void	searchComponent(SwimmingCompetition* competition);
void	PrintFindMenu();
int		saveSystemToFile(DirectorSwimmingCompetition* director);
