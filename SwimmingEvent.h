#ifndef SWIMMINGEVENT
#define SWIMMINGEVENT

#include"SwimmingHeat.h"

typedef enum
{
	eFreestyle, eButterfly, eBackstroke, eBreaststroke, eNumOfStyle
}eStyle;

static const char* StyleTypeStr[eNumOfStyle];

typedef enum
{
	e50m, e100m, e200m, eNumOfDistance
}eDistance;

static const char* DistanceTypeStr[eNumOfDistance];


typedef struct
{
	int worldRecord;
	int competitionRecord;
	SwimmingHeat* heatArr;
	int countHeat;
	eStyle style;
	eDistance distance;
}SwimmingEvent;

int		compareWorldRec(const SwimmingEvent* event1,const SwimmingEvent* event2);
int		compareCompetitionRec(const SwimmingEvent* event1, const SwimmingEvent* event2);
int		addHeat(SwimmingEvent* event, SwimmingHeat* heat);
void	freeEvent(SwimmingEvent* events, int count);
void	freeHeatArr(SwimmingEvent* events);
int		initEvent(SwimmingEvent* event, int worldRec, int competitionRec, eStyle style, eDistance distance);
void	printEvent(const SwimmingEvent* event);
eStyle	getStyle();
eDistance getDistance();
void	printHeatsArr(SwimmingHeat* heats, int count);
char*	getEventName(SwimmingEvent* event);



#endif