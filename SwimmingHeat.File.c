#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SwimmingHeat.File.h"
#include"General.h"
#include"DirectorSwimmingCompetitionFile.h"

int readSwimmerDetailsFile(FILE* file, Swimmer* swimmer)
{
    if (file == NULL || swimmer == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    if (myGetsF(buffer, sizeof(buffer), file) == NULL)
    {
        return 0;
    }
    swimmer->name = _strdup(buffer);
    if (swimmer->name == NULL)
    {
        COLSE_RETURN_0(file);
    }
    swimmer->name[strcspn(swimmer->name, "\n")] = '\0';
    
    if (fscanf(file, "%d\n", &swimmer->age) != 1)
    {
        COLSE_RETURN_0(file);
    }
    
    if (fscanf(file, "%d", &swimmer->bestResult) != 1)
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readHeatDetailsFile(FILE* file, SwimmingHeat* heat)
{
    if (file == NULL || heat == NULL)
    {
        return 0;
    }
    if (!readHeatTypeFromFile(file, &heat->type))
    {
        COLSE_RETURN_0(file);
    }
   
    if (fscanf(file, "%d\n", &heat->numReferees) != 1)
    {
        COLSE_RETURN_0(file);
    }
   
    heat->refereeArr = (Referee*)malloc(heat->numReferees * sizeof(Referee));
    if (heat->refereeArr == NULL)
    {
        free(heat->refereeArr);
        return 0;
    }
    for (int i = 0; i < heat->numReferees; i++)
    {
        if (!readRefereeDetailsFile(file, &heat->refereeArr[i]))
        {
            COLSE_RETURN_0(file);
        }
    }
    
    if(fscanf(file, "%d\n", &heat->numOfSwimmers) != 1)
    {
        COLSE_RETURN_0(file);
    }
    
    heat->swimmerArr = (Swimmer**)malloc(heat->numOfSwimmers * sizeof(Swimmer*));
    if (heat->swimmerArr == NULL)
    {
        free(heat->swimmerArr);
        return 0;
    }
    for (int i = 0; i < heat->numOfSwimmers; i++)
    {
        heat->swimmerArr[i] = (Swimmer*)malloc(sizeof(Swimmer));
        if (heat->swimmerArr[i] == NULL)
        {
            for (int j = 0; j < i; j++) 
            {
                free(heat->swimmerArr[j]);
            }
            free(heat->swimmerArr);
            COLSE_RETURN_0(file);
        }
        heat->swimmerArr[i]->name = NULL;
        heat->swimmerArr[i]->age = 0;
        heat->swimmerArr[i]->bestResult = 0;
        if (!readSwimmerDetailsFile(file, heat->swimmerArr[i]))
        {
            for (int j = 0; j <= i; j++)
            {
                free(heat->swimmerArr[j]);
            }
            COLSE_RETURN_0(file);
        }
    }
    return 1;
}
int readCoachDetailsFile(FILE* file, Coach* coach)
{
    if (file == NULL || coach == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    myGetsF(buffer, sizeof(buffer), file);
    coach->name = _strdup(buffer);
    buffer[0] = '\0';
    coach->name[strcspn(coach->name, "\n")] = '\0';

    if (fscanf(file, "%d\n", &coach->age) != 1)
    {
        COLSE_RETURN_0(file);
    }

    if (fscanf(file, "%d\n", &coach->experience) != 1)
    {
        COLSE_RETURN_0(file);
    }

    char buffer2[MAX_STR_LEN];
    myGetsF(buffer2, sizeof(buffer2), file);
    coach->country = _strdup(buffer2);
    buffer2[0] = '\0';
    coach->country[strcspn(coach->country, "\n")] = '\0';

    if (fscanf(file, "%d\n", &coach->numOfChamps) != 1)
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readRefereeDetailsFile(FILE* file, Referee* referee)
{
    if (file == NULL || referee == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    myGetsF(buffer, sizeof(buffer), file);
    referee->name = _strdup(buffer);
    buffer[0] = '\0';
    referee->name[strcspn(referee->name, "\n")] = '\0';
    
    if (fscanf(file, "%d\n", &referee->age) != 1)
    {
        COLSE_RETURN_0(file);
    }

    char buffer2[MAX_STR_LEN];
    myGetsF(buffer2, sizeof(buffer2), file);
    referee->country = _strdup(buffer2);
    buffer2[0] = '\0';
    referee->country[strcspn(referee->country, "\n")] = '\0';

    char buffer3[MAX_STR_LEN];
    myGetsF(buffer3, sizeof(buffer3), file);
    buffer3[strcspn(buffer3, "\n")] = '\0';
    if (strcmp(buffer3, "Side") == 0)
    {
        referee->refType = eSide;
    }
    else if (strcmp(buffer3, "Spingboard") == 0)
    {
        referee->refType = eSpingboard;
    }
    else if (strcmp(buffer3, "Main") == 0)
    {
        referee->refType = eMain;
    }
    else
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readHeatTypeFromFile(FILE* file, eHeatType* heatType)
{
    char buffer[MAX_STR_LEN];
    myGetsF(buffer, sizeof(buffer), file);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strcmp(buffer, "Qualifiers") == 0)
    {
        *heatType = eQualifiers;
    }
    else if (strcmp(buffer, "SemiFinal") == 0)
    {
        *heatType = eSemiFinal;
    }
    else if (strcmp(buffer, "Final") == 0)
    {
        *heatType = eFinal;
    }
    else
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readHeatFromBinaryFile(FILE* file, SwimmingHeat* heat) 
{
    if (fread(&heat->type, sizeof(int), 1, file) != 1 ||
        fread(&heat->numReferees, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    if (!readRefereesFromBinaryFile(file, heat)) 
    {
            COLSE_RETURN_0(file);
    }
    if (fread(&heat->numOfSwimmers, sizeof(int), 1, file) != 1)
    {
        COLSE_RETURN_0(file);

    }
   
   if (!readSwimmersFromBinaryFile(file, heat)) 
   {
        COLSE_RETURN_0(file);
   }
    return 1;
}
int readRefereesFromBinaryFile(FILE* file, SwimmingHeat* heat) 
{
    heat->refereeArr = (Referee*)malloc(sizeof(Referee) * heat->numReferees);
    if (heat->refereeArr == NULL) 
    {
        return 0;
    }
    for (int i = 0; i < heat->numReferees; i++) 
    {
        if (!readRefereeFromBinaryFile(file, &heat->refereeArr[i])) 
        {
            free(heat->refereeArr); 
            COLSE_RETURN_0(file);
        }
    }
    return 1;
}

int readRefereeFromBinaryFile(FILE* file, Referee* referee) 
{
    referee->name = readStringFromBinaryFile(file);
    if (!referee->name) 
    {
        COLSE_RETURN_0(file);
    }
    if (fread(&referee->age, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    referee->country = readStringFromBinaryFile(file);
    if (!referee->country) 
    {
        COLSE_RETURN_0(file);
    }
    if (fread(&referee->refType, sizeof(int), 1, file) != 1)
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}
int readSwimmersFromBinaryFile(FILE* file, SwimmingHeat* heat) 
{
    
    heat->swimmerArr = (Swimmer**)malloc(sizeof(Swimmer*) * heat->numOfSwimmers);
    if (heat->swimmerArr == NULL) 
    {
        return 0;
    }
    for (int i = 0; i < heat->numOfSwimmers; i++) 
    {
        heat->swimmerArr[i] = (Swimmer*)malloc(sizeof(Swimmer));
        if (heat->swimmerArr[i] == NULL)
        {
            freeSwimmerArr(heat->swimmerArr, i);
            return 0;
        }
        if (!readSwimmerFromBinaryFile(file, heat->swimmerArr[i])) 
        {
            freeSwimmerArr(heat->swimmerArr,heat->numOfSwimmers);
            COLSE_RETURN_0(file);
        }
    }
    return 1;
}

int readSwimmerFromBinaryFile(FILE* file, Swimmer* swimmer) 
{
    swimmer->name = readStringFromBinaryFile(file);
    if (!swimmer->name) 
    {
        COLSE_RETURN_0(file);
    }
    if (fread(&swimmer->age, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    if (fread(&swimmer->bestResult, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }
    return 1;
}