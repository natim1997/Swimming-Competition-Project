#ifndef SWIMMINGHEAT
#define SWIMMINGHEAT
#define MAX_SWIMMERS_PER_HEAT 8
#define MAX_REFEREES_PER_HEAT 3


#include "Swimmer.h"
#include "Referee.h"
#include "Team.h"


typedef enum
{
	eQualifiers, eSemiFinal, eFinal, eNumOfHeatType
}eHeatType;

static const char* HeatTypeStr[eNumOfHeatType];


typedef struct
{
	Swimmer** swimmerArr;
	int numOfSwimmers;
	int numReferees;
	int* timeResultArr;
	int counterTime;
	Referee* refereeArr;
	eHeatType type;
}SwimmingHeat;

int		initHeat(SwimmingHeat* heat, int numOfHeats, eHeatType type, Referee ref);
void	printHeat(const SwimmingHeat* heat);
void	freeHeat(SwimmingHeat* heat);
void	freeRefArr(SwimmingHeat* heat);
int		setResultToSwimmer(SwimmingHeat* heat, int swimmerIndex, int time);
void	printResult(double* results, int count);
void	printHeatToEvent(SwimmingHeat* heat);
void	addRefereesToHeat(SwimmingHeat* heat);
eHeatType getHeatType();
void	printSwimmerArr(Swimmer** swimmers, int count);
void	printSwimmerPtr(void* element);
void	freeSwimmerArr(Swimmer** swimmers, int count);
void	freeSwimmerPtr(void* element);
void	printHeatsArr(SwimmingHeat* heats, int count);
void	printHeatNew(void* element);
void	printRefNew(void* element);






#endif