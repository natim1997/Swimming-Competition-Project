#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include"Team.h"
#include"General.h"
#include"SwimmingHeat.h"
static const char* swimmerSortOptStr[] = { "Name", "Age" };


Team* initTeamToCompetition()
{
    Team* team = (Team*)malloc(sizeof(Team));
    if (team == NULL) 
        return NULL; 

    team->country = NULL;
    team->countryCode[0] = '\n';
    team->teamSwimmerArr = NULL;
    team->capacity = 0;
    team->swimmersCount = 0;
    team->numOfMedals = 0;
    team->numOfChampionship = 0;
    team->numOfWorldRecord = 0;
    team->teamCoach = NULL;    
    return team; 
}

int initTeam(Team* team,char* country,char* countryCode)
{
    if (!team)
        return 0;
    
    team->country = _strdup(country);
    if (team->country == NULL || team->cheeringChants == NULL)
    {
        free(team->country);
        return 0;
    }
    strncpy(team->countryCode, countryCode, CODE_LEN);
    team->countryCode[CODE_LEN] = '\0';
    team->teamSwimmerArr = NULL;
    team->swimmersCount = 0;
    team->numOfMedals = 0;
    team->numOfChampionship = 0;
    team->numOfWorldRecord = 0;
    team->teamCoach = NULL;
    return 1;
}


char* getCountryName(Team* team)
{
    if (team == NULL)
    {
        return NULL;
    }
    return team->country;
}

void getCountryCode(char* code)
{
    char temp[255];
    int ok = 1;
    do 
    {
        ok = 1;
        printf("Enter country code  - %d UPPER CASE letters\t", CODE_LEN);
        myGets(temp, 255, stdin);
        if (strlen(temp) != CODE_LEN)
        {
            printf("code should be %d letters\n", CODE_LEN);
            ok = 0;
        }
        else 
        {
            for (int i = 0; i < CODE_LEN; i++)
            {
                if (isupper(temp[i]) == 0)
                {
                    printf("Need to be upper case letter\n");
                    ok = 0;
                    break;
                }
            }
        }
    } while (!ok);
    strcpy(code, temp);
}

void printTeamSwimmers(const Team* team)
{
    if (team == NULL || team->teamSwimmerArr == NULL)
    {
        printf("No swimmers in the team.\n");
        return;
    }
    for (int i = 0; i < team->swimmersCount; i++)
    {
        printSwimmer(team->teamSwimmerArr[i]);
    }
}


int addCoach(Team* team, Coach* coach)
{
    if (team == NULL || coach == NULL)
    {
        return 0;
    }
    team->teamCoach = coach;
    return 1;
}


void freeTeam(Team* team,int count)
{
    if (team != NULL)
    {
        for (int i = 0; i < count; i++)
        {
            free(team->country);
            free(team->cheeringChants);
            freeTeamSwimmers(team);
        }
    }
}


void freeTeamSwimmers(Team* team)
{
    if (team != NULL && team->teamSwimmerArr != NULL)
    {
        for (int i = 0; i < team->swimmersCount; i++)
        {
            freeSwimmer(team->teamSwimmerArr[i]);
        }
        free(team->teamSwimmerArr);
    }
}


void printTeam(const Team* team)
{
    if (team == NULL)
    {
        printf("No team data.\n");
        return;
    }
    printf("Team Country : %s\nTeam code : %s\nNumber of medals : %d\nNumber of championships : %d\nNumber of world records : %d\n",
        team->country, team->countryCode, team->numOfMedals,team->numOfChampionship, team->numOfWorldRecord);
    if (team->teamCoach != NULL)
    {
        printCoach(team->teamCoach);
        printf("------------------\n");
    }
    printf("There are %d Swimmers in this team\n", team->swimmersCount);
    printSwimmerArr(team->teamSwimmerArr,team->swimmersCount);
    printf("------------------\n");
}
int setCoachToTeam(Team* team, Coach* coach)
{
    if (team == NULL || coach == NULL)
    {
        return 0;
    }
    team->teamCoach = coach;
    return 1;
}

void printSwimmerArrToTeam(const Swimmer** swimmers, int count)
{
    if (swimmers == NULL)
    {
        printf("No swimmers.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        if (swimmers[i] != NULL)
        {
            printf("%d - ", i + 1);
            printf("Swimmer name : %s\n", swimmers[i]->name);
            printf("Swimmer age : %d\n", swimmers[i]->age);
            printf("Best result of the swimmer : %d\n", swimmers[i]->bestResult);
        }
    }
}
