#ifndef _SWIMMINGEVENTFILE_
#define _SWIMMINGEVENTFILE_
#include"SwimmingEvent.h"


int		readStyleFile(FILE* file, eStyle* style);
int		readDistanceFile(FILE* file, eDistance* distance);
int		readEventFromBinaryFile(FILE* file, SwimmingEvent* event);


#endif
