#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SwimmingCompetitionFile.h"
#include"General.h"
#include"SwimmingHeat.File.h"
#include"Swimmer.h"
#include"DirectorSwimmingCompetitionFile.h"
#include"SwimmingEventFile.h"

int readCompetitionDetailsFile(FILE* file, SwimmingCompetition* comp)
{
    if (file == NULL || comp == NULL)
        return 0;
    int nameLen;
    fscanf(file, "%d\n", &nameLen);
    comp->competitionName = (char*)malloc(nameLen + 1);
    if (comp->competitionName == NULL)
    {
        free(comp->competitionName);
        COLSE_RETURN_0(file);
    }
    
    char buffer[MAX_STR_LEN] = {0};
    myGetsF(buffer, sizeof(buffer), file);
    comp->competitionName = _strdup(buffer);
    buffer[0] = '\0';
    comp->competitionName[strcspn(comp->competitionName, "\n")] = '\0';

    comp->address = (Address*)malloc(sizeof(Address));
    if (comp->address == NULL)
    {
        free(comp->competitionName);
        free(comp->address);
        COLSE_RETURN_0(file);
    }
    if (!readAddressFile(file, comp->address))
    {
        COLSE_RETURN_0(file);
    }
    comp->date = (Date*)malloc(sizeof(Date));
    if (comp->date == NULL) {
        free(comp->competitionName);
        free(comp->address);
        free(comp->date);
        COLSE_RETURN_0(file);
    }
    if (!readDateFile(file, comp->date)) 
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readAddressFile(FILE* file, Address* address)
{
    if (file == NULL || address == NULL)
    {
        return 0;
    }
    int countryLen;
    fscanf(file, "%d\n", &countryLen);
    address->country = (char*)malloc(countryLen + 1);
    if (address->country == NULL)
    {
        free(address->country);
        return 0;
    }
    char buffer[MAX_STR_LEN] = { 0 };
    myGetsF(buffer, sizeof(buffer), file);
    address->country = _strdup(buffer);
    buffer[0] = '\0';
    address->country[strcspn(address->country, "\n")] = '\0';
    
    int cityLen;
    fscanf(file, "%d\n", &cityLen);
    address->city = (char*)malloc(cityLen + 1);
    if (address->city == NULL)
    {
        free(address->country);
        free(address->city);
        return 0;
    }
    char buffer2[MAX_STR_LEN] = { 0 };
    myGetsF(buffer2, sizeof(buffer), file);
    address->city = _strdup(buffer2);
    buffer2[0] = '\0';
    address->city[strcspn(address->city, "\n")] = '\0';
    return 1;
}
int readDateFile(FILE* file, Date* date)
{
    if (file == NULL || date == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    if (fgets(buffer, sizeof(buffer), file) == NULL)
    {
        COLSE_RETURN_0(file);
    }
    if (sscanf(buffer, "%d/%d/%d", &date->day, &date->month, &date->year) != 3)
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readTeamDetailsFile(FILE* file, Team* team)
{
    if (file == NULL || team == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN] = { 0 };
    myGetsF(buffer, sizeof(buffer), file);
    team->country = _strdup(buffer);
    buffer[0] = '\0';

    team->country[strcspn(team->country, "\n")] = '\0';
    char buffer2[CODE_LEN + 1];
    myGetsF(buffer2, sizeof(buffer2), file);
    buffer2[strcspn(buffer2, "\n")] = '\0';
    strncpy(team->countryCode, buffer2, CODE_LEN);
    team->countryCode[CODE_LEN] = '\0';
    
    if (fscanf(file, "%d\n", &team->numOfMedals) != 1)
    {
        COLSE_RETURN_0(file);
    }

    if (fscanf(file, "%d\n", &team->numOfChampionship) != 1)
    {
        COLSE_RETURN_0(file);
    }
    
    if (fscanf(file, "%d\n", &team->numOfWorldRecord) != 1)
    {
        COLSE_RETURN_0(file);
    }
    team->teamCoach = (Coach*)malloc(sizeof(Coach));
    if (team->teamCoach == NULL)
    {
        free(team->teamCoach);
        return 0;
    }
    readCoachDetailsFile(file, team->teamCoach);

    if (fscanf(file, "%d\n", &team->swimmersCount) != 1)
    {
        COLSE_RETURN_0(file);
    }
    team->teamSwimmerArr = (Swimmer**)malloc(team->swimmersCount * sizeof(Swimmer*));
    if (team->teamSwimmerArr == NULL)
    {
        free(team->country);
        free(team->teamCoach);
        return 0;
    }
    for (int i = 0; i < team->swimmersCount; i++)
    {
        team->teamSwimmerArr[i] = (Swimmer*)malloc(sizeof(Swimmer));
        if (team->teamSwimmerArr[i] == NULL)
        {
            
            freeSwimmerArr(team->teamSwimmerArr,team->swimmersCount);
            free(team->country);
            free(team->teamCoach);
            return 0;
        }
        readSwimmerDetailsFile(file, team->teamSwimmerArr[i]);
    }
    return 1;
}
int writeStringToCompetitionFile(FILE* fp, const char* string)
{
    if (string == NULL)
    {
        size_t zero = 0;
        return fwrite(&zero, sizeof(size_t), 1, fp) == 1;

    }
    size_t len = strlen(string);
    if (fwrite(&len, sizeof(size_t), 1, fp) != 1)
        COLSE_RETURN_0(fp);
    if (fwrite(string, sizeof(char), len, fp) != len) 
        COLSE_RETURN_0(fp);
    return 1;
}
// Function to save a Coach data to file
//int saveCoachToBinaryFileCompressed(const Coach* coach, FILE* fp) //readint work but string not .. no have time for this :(
//{
//    if (coach == NULL || fp == NULL)
//        return 0;
//
//    BYTE buffer[4] = { 0 };
//    BYTE nameLen = (BYTE)strlen(coach->name);
//    BYTE countryLen = (BYTE)strlen(coach->country);
//    buffer[0] = coach->age >> 5;
//    buffer[1] = (coach->age << 3) | (coach->experience >> 3);
//    buffer[2] = (coach->experience << 5) | coach->numOfChamps; 
//    buffer[3] = (nameLen << 4) | countryLen;
//    
//    if (fwrite(buffer, sizeof(BYTE), 3, fp) != 3) 
//    {
//        COLSE_RETURN_0(fp);
//    }
//    
//    if (fwrite(coach->name, sizeof(char), nameLen, fp) != nameLen ||
//        fwrite(coach->country, sizeof(char), countryLen, fp) != countryLen) {
//        return 0;
//    }
//        return 1;
//}

int readCompetitionFromFile(FILE* file, SwimmingCompetition* competition) 
{
    competition->competitionName = readStringFromBinaryFile(file);
    if(!competition->competitionName)
    {
        COLSE_RETURN_0(file);
    }
    competition->address = (Address*)malloc(sizeof(Address));
    if (!competition->address)
    {
        printf("Failed to allocate memory for address.\n");
        return 0;
    }
    competition->address->country = readStringFromBinaryFile(file);
    if(!competition->address->country)
    {
        COLSE_RETURN_0(file);
    }
    competition->address->city = readStringFromBinaryFile(file);
    if (!competition->address->city)
    {
        COLSE_RETURN_0(file);
    } 
    competition->date = (Date*)malloc(sizeof(Date));
    if (!competition->date)
    {
        printf("Failed to allocate memory for date.\n");
        return 0;
    }
    if(fread(competition->date,sizeof(Date),1,file) != 1)
    {
        COLSE_RETURN_0(file);
    }
    if (fread(&competition->countEvent, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    competition->eventArr = (SwimmingEvent*)malloc(sizeof(SwimmingEvent) * competition->countEvent);
    for (int i = 0; i < competition->countEvent; i++) 
    {
        if (!readEventFromBinaryFile(file, &competition->eventArr[i])) 
        {
            COLSE_RETURN_0(file);
        }
    }

    if (fread(&competition->numOfTeams, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    competition->teamArr = (Team*)malloc(sizeof(Team) * competition->numOfTeams);
    for (int j = 0; j < competition->numOfTeams; j++) {
        if (!readTeamFromBinaryFile(file, &competition->teamArr[j])) 
        {
            COLSE_RETURN_0(file);
        }
    }

    return 1;
}
int readDateFromBinaryFile(FILE* file, Date* date) 
{
    if (file == NULL || date == NULL) 
        return 0;

    if (!readIntFromBinaryFile(file, &date->day)) 
        COLSE_RETURN_0(file);

    if (!readIntFromBinaryFile(file, &date->month)) 
        COLSE_RETURN_0(file);

    if (!readIntFromBinaryFile(file, &date->year)) 
        COLSE_RETURN_0(file);
    return 1;
}
int readTeamFromBinaryFile(FILE* file, Team* team) 
{
    if (file == NULL || team == NULL)
        return 0;

    team->country = readStringFromBinaryFile(file);
    if (!team->country)
    {
        COLSE_RETURN_0(file);
    }

    if (!readCharsFromFile(team->countryCode,CODE_LEN+1, file))
    {
        COLSE_RETURN_0(file);
    }
    if (!readIntFromBinaryFile(file, &team->numOfMedals)) 
        COLSE_RETURN_0(file);
    if (!readIntFromBinaryFile(file, &team->numOfChampionship)) 
        COLSE_RETURN_0(file);
    if (!readIntFromBinaryFile(file, &team->numOfWorldRecord)) 
        COLSE_RETURN_0(file);

    team->teamCoach = (Coach*)malloc(sizeof(Coach));
    if (team->teamCoach == NULL) 
        return 0;
    team->teamCoach->name = readStringFromBinaryFile(file);
    if (!team->teamCoach->name)
    {
        COLSE_RETURN_0(file);
    }
    if (!readIntFromBinaryFile(file, &team->teamCoach->age))
        COLSE_RETURN_0(file);
    if (!readIntFromBinaryFile(file, &team->teamCoach->experience))
        COLSE_RETURN_0(file);
    team->teamCoach->country = readStringFromBinaryFile(file);
    if (!team->teamCoach->country)
        COLSE_RETURN_0(file);
    if (!readIntFromBinaryFile(file, &team->teamCoach->numOfChamps))
        COLSE_RETURN_0(file);
    if (!readIntFromBinaryFile(file, &team->swimmersCount)) 
        COLSE_RETURN_0(file);

    team->teamSwimmerArr = (Swimmer**)malloc(sizeof(Swimmer*) * team->swimmersCount);
    if (team->teamSwimmerArr == NULL) return 0;

    for (int i = 0; i < team->swimmersCount; i++) 
    {
        team->teamSwimmerArr[i] = (Swimmer*)malloc(sizeof(Swimmer));
        if (!readSwimmerFromBinaryFile(file, team->teamSwimmerArr[i])) 
        {
            COLSE_RETURN_0(file);
        }
    }
    return 1;
}
int readCoachFromBinaryFileCompressed(Coach* coach, FILE* fp) {
    if (coach == NULL || fp == NULL)
        return 0;

    BYTE buffer[4]; 

    if (fread(buffer, sizeof(BYTE), 3, fp) != 3)
        return 0; 

    coach->age = (buffer[0] << 5); 
    coach->age |= (buffer[1] >> 3);
    coach->experience = (buffer[1] << 3); 
    coach->experience |= (buffer[2] >> 5); 
    coach->numOfChamps = (buffer[2] & 0x1F); 

    
    BYTE nameLen = (buffer[3] >> 4); 
    BYTE countryLen = (buffer[3] & 0x0F);

    coach->name = (char*)malloc(nameLen + 1); 
    coach->country = (char*)malloc(countryLen + 1); 

    if (coach->name == NULL || coach->country == NULL)
        return 0; 

    if (fread(coach->name, sizeof(char), nameLen, fp) != nameLen ||
        fread(coach->country, sizeof(char), countryLen, fp) != countryLen) {
        free(coach->name);
        free(coach->country);
        return 0;
    }

    coach->name[nameLen] = '\0';
    coach->country[countryLen] = '\0';

    return 1; 
}
