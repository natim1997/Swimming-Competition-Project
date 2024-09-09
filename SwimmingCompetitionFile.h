#ifndef _SWIMMINGCOMPETITIONFILE_
#define _SWIMMINGCOMPETITIONFILE_
typedef unsigned char BYTE;
#include"SwimmingCompetition.h"

int		readCompetitionDetailsFile(FILE* file, SwimmingCompetition* comp);
int		readAddressFile(FILE* file, Address* address);
int		readDateFile(FILE* file, Date* date);
int		readTeamDetailsFile(FILE* file, Team* team);
int		writeStringToCompetitionFile(FILE* fp, const char* string);
int		readCompetitionFromFile(FILE* file, SwimmingCompetition* competition);
int		readDateFromBinaryFile(FILE* file, Date* date);
int		readTeamFromBinaryFile(FILE* file, Team* team);
int		readCoachFromBinaryFileCompressed(Coach* coach, FILE* fp);
#endif
