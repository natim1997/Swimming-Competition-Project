#ifndef _DIRECTORSWIMMINGCOMPETITIONFILE_
#define _DIRECTORSWIMMINGCOMPETITIONFILE_

#include"DirectorSwimmingCompetition.h"
#include"SwimmingCompetitionFile.h"
#include"General.h"


int		loadSwimmingCompetitionFromTextFile(DirectorSwimmingCompetition* pDirector,const char* fileName);
int		saveCompetitionToTextFile(DirectorSwimmingCompetition* director, SwimmingCompetition* competition, const char* fileName);
int		loadSwimmingCompetitionFromBinaryFile(DirectorSwimmingCompetition* pDirector, const char* fileName);
int		saveCompetitionToBinaryFile(DirectorSwimmingCompetition* director, SwimmingCompetition* competition,const char* fileName);
int		writeStringToFile(const char* str, FILE* fp);
int		writeIntToFile(int value, FILE* fp);
int		writeDoubleToFile(double value, FILE* fp);
int		writeCharsToFile(const char* arr, int size, FILE* fp);
int		readIntFromBinaryFile(FILE* fp, int* value);
int		readDoubleFromBinaryFile(FILE* fp, double* value);
char*	readStringFromBinaryFile(FILE* fp);
int		readCharsFromFile(char* arr, int length, FILE* fp);
const char* getStyleName(int style);
const char* getDistanceName(int distance);
const char* getRefereeNameType(int type);
const char* getHeatNameType(int type);

#endif