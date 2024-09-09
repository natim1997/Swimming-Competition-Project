#ifndef _SWIMMINGHEATFILE_
#define _SWIMMINGHEATFILE_

#include"SwimmingHeat.h"

int		readSwimmerDetailsFile(FILE* file, Swimmer* swimmer);
int		readHeatDetailsFile(FILE* file, SwimmingHeat* heat);
int		readCoachDetailsFile(FILE* file, Coach* coach);
int		readRefereeDetailsFile(FILE* file, Referee* referee);
int		readHeatTypeFromFile(FILE* file, eHeatType* heatType);
int		readHeatFromBinaryFile(FILE* file, SwimmingHeat* heat);
int		readRefereesFromBinaryFile(FILE* file, SwimmingHeat* heat);
int		readRefereeFromBinaryFile(FILE* file, Referee* referee);
int		readSwimmersFromBinaryFile(FILE* file, SwimmingHeat* heat);
int		readSwimmerFromBinaryFile(FILE* file, Swimmer* swimmer);
#endif