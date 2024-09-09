#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"DirectorSwimmingCompetitionFile.h"
#include"SwimmingEventFile.h"
#include"SwimmingHeat.File.h"




int loadSwimmingCompetitionFromTextFile(DirectorSwimmingCompetition* pDirector,const char* fileName)
{
    if (fileName == NULL)
        return 0;
    FILE* file = fopen(fileName, "r");
    
    if (file == NULL)
        return 0;
    
    if (fscanf(file, "%d", &pDirector->countCompetition) != 1)
        COLSE_RETURN_0(file);
    
    if (!L_init(&(pDirector->SwimmingCompetitonList)))
        COLSE_RETURN_0(file);
    
    for (int c = 0; c < pDirector->countCompetition; c++)
    {
        SwimmingCompetition* newCompetition = malloc(sizeof(SwimmingCompetition));
        if (newCompetition == NULL) 
        {
            COLSE_RETURN_0(file);
        }
        if (!readCompetitionDetailsFile(file, newCompetition))
        {
            free(newCompetition);
            COLSE_RETURN_0(file);
        }
        if (fscanf(file, "%d", &newCompetition->countEvent) != 1)
        {
            free(newCompetition);
            COLSE_RETURN_0(file);
        }
        newCompetition->eventArr = (SwimmingEvent*)malloc(newCompetition->countEvent * sizeof(SwimmingEvent));
        if (newCompetition->eventArr == NULL)
        {
            free(newCompetition);
            COLSE_RETURN_0(file);
        }
        for (int e = 0; e < newCompetition->countEvent; e++)
        {
            if (readStyleFile(file, &newCompetition->eventArr[e].style) == 0)
            {
                free(newCompetition->eventArr);
                free(newCompetition);
                COLSE_RETURN_0(file);
            }
            if (readDistanceFile(file, &newCompetition->eventArr[e].distance) == 0)
            {
                free(newCompetition->eventArr);
                free(newCompetition);
                COLSE_RETURN_0(file);
            }
            if (fscanf(file, "%d", &newCompetition->eventArr[e].countHeat) != 1)
            {
                free(newCompetition->eventArr);
                free(newCompetition);
                COLSE_RETURN_0(file);
            }
            newCompetition->eventArr[e].heatArr = (SwimmingHeat*)malloc(newCompetition->eventArr[e].countHeat * sizeof(SwimmingHeat));
            if (newCompetition->eventArr[e].heatArr == NULL)
            {
                free(newCompetition->eventArr);
                free(newCompetition);
                COLSE_RETURN_0(file);
            }
            for (int h = 0; h < newCompetition->eventArr[e].countHeat; h++)
            {
                if (readHeatDetailsFile(file, (&newCompetition->eventArr[e].heatArr[h])) == 0)
                {
                    free(newCompetition->eventArr[e].heatArr);
                    free(newCompetition->eventArr);
                    free(newCompetition);
                    COLSE_RETURN_0(file);
                }

            }
        }
        if (fscanf(file, "%d", &newCompetition->numOfTeams) != 1)
        {
            free(newCompetition);
            COLSE_RETURN_0(file);
        }
        
        newCompetition->teamArr = (Team*)malloc(newCompetition->numOfTeams * sizeof(Team));
        if (newCompetition->teamArr == NULL) 
        {
            free(newCompetition);
            COLSE_RETURN_0(file);
        }
        for (int t = 0; t < newCompetition->numOfTeams; t++) 
        {
            if (!readTeamDetailsFile(file, &newCompetition->teamArr[t])) 
            {
                for (int t2 = 0; t2 < t; t2++) 
                {
                    free(newCompetition->teamArr[t2].teamSwimmerArr);
                    free(newCompetition->teamArr[t2].teamCoach);
                }
                free(newCompetition->teamArr);
                free(newCompetition->eventArr);
                free(newCompetition);
                COLSE_RETURN_0(file);
            }
        }
        //need to free newCompetition
        L_insert(&(pDirector->SwimmingCompetitonList.head), newCompetition);
    }
    fclose(file);
    return 1;
}



int saveCompetitionToTextFile(DirectorSwimmingCompetition* director,SwimmingCompetition* competition ,const char* fileName) 
{
    FILE* fp = fopen(fileName, "w");  
    if (!fp) 
    {
        printf("Error opening file to write\n");
        return 0;
    }

    fprintf(fp, "%d\n%s\n%s\n%s\n", director->countCompetition, competition->competitionName, competition->address->country, competition->address->city);
    fprintf(fp, "%d/%d/%d\n", competition->date->day, competition->date->month, competition->date->year);
    fprintf(fp, "%d\n", competition->countEvent);
        

    for (int i = 0; i < competition->countEvent; i++) 
    {
        SwimmingEvent* event = &competition->eventArr[i];
        fprintf(fp, "%s\n%s\n%d\n", getStyleName(event->style), getDistanceName(event->distance), event->countHeat);
           

        for (int j = 0; j < event->countHeat; j++) 
        {
            SwimmingHeat* heat = &event->heatArr[j];
            fprintf(fp, "%s\n%d\n", getHeatNameType(heat->type), heat->numReferees);
                

            for (int k = 0; k < heat->numReferees; k++) 
            {
                Referee* referee = &heat->refereeArr[k];
                fprintf(fp, "%s\n%d\n%s\n%s\n", referee->name, referee->age, referee->country, getRefereeNameType(referee->refType));
                    
            }
            fprintf(fp, "%d\n", heat->numOfSwimmers);
                
            for (int m = 0; m < heat->numOfSwimmers; m++) 
            {
                Swimmer* swimmer = heat->swimmerArr[m];
                fprintf(fp, "%s\n%d\n%d\n", swimmer->name, swimmer->age, swimmer->bestResult);
                   
            }
        }
    }

    if(fprintf(fp, "%d\n", competition->numOfTeams)<0)
        COLSE_RETURN_0(fp);
    for (int n = 0; n < competition->numOfTeams; n++) 
    {
        Team* team = &competition->teamArr[n];
        fprintf(fp, "%s\n%s\n%d\n%d\n%d\n", team->country, team->countryCode, team->numOfMedals, team->numOfChampionship, team->numOfWorldRecord);
            

        Coach* coach = team->teamCoach;
        fprintf(fp, "%s\n%d\n%d\n%s\n%d\n", coach->name, coach->age, coach->experience, coach->country, coach->numOfChamps);
          
        fprintf(fp, "%d\n", team->swimmersCount);
        for (int p = 0; p < team->swimmersCount; p++) 
        {
            Swimmer* swimmer = team->teamSwimmerArr[p];
            fprintf(fp, "%s\n%d\n%d\n", swimmer->name, swimmer->age, swimmer->bestResult);
                
        }
    }
    fclose(fp);
    return 1;
}

int loadSwimmingCompetitionFromBinaryFile(DirectorSwimmingCompetition* director, const char* fileName) 
{
    FILE* file = fopen(fileName, "rb");
    if (!file) 
    {
        printf("Error opening binary file for reading.\n");
        return 0;
    }

    
    if (fread(&director->countCompetition, sizeof(int), 1, file) != 1) 
    {
        COLSE_RETURN_0(file);
    }

    // Initialize the competition list
    if (!L_init(&director->SwimmingCompetitonList)) 
    {
        COLSE_RETURN_0(file);
    }

    for (int i = 0; i < director->countCompetition; i++) 
    {
        SwimmingCompetition* newCompetition = (SwimmingCompetition*)malloc(sizeof(SwimmingCompetition));
        if (!newCompetition) 
            COLSE_RETURN_0(file);
        if (!readCompetitionFromFile(file, newCompetition)) 
        {
            freeDirector(director);
            COLSE_RETURN_0(file);
        }

        L_insert(&(director->SwimmingCompetitonList.head), newCompetition);
    }

    fclose(file);
    return 1;
}


int saveCompetitionToBinaryFile(DirectorSwimmingCompetition* director,SwimmingCompetition* competition,const char* fileName) 
{
    FILE* fp = fopen(fileName, "wb");
    if (!fp) 
    {
        printf("Error opening file to write\n");
        return 0;
    }
    
    if (!writeIntToFile(director->countCompetition, fp)) 
        COLSE_RETURN_0(fp);
   
    if (!writeStringToFile(competition->competitionName, fp))   
        COLSE_RETURN_0(fp);
    
    if(!writeStringToFile(competition->address->country, fp))
        COLSE_RETURN_0(fp);
    
    if(!writeStringToFile(competition->address->city, fp))
        COLSE_RETURN_0(fp);

    if(fwrite(competition->date, sizeof(Date), 1, fp)!= 1)
        COLSE_RETURN_0(fp);

    if (!writeIntToFile(competition->countEvent, fp))
        COLSE_RETURN_0(fp);
   
    for (int i = 0; i < competition->countEvent; i++) 
    {
        SwimmingEvent* event = &competition->eventArr[i];
        
        if(!writeIntToFile(event->style, fp))
            COLSE_RETURN_0(fp);
        
        if(!writeIntToFile(event->distance, fp))
            COLSE_RETURN_0(fp);
        
        if(!writeIntToFile(event->countHeat, fp))
            COLSE_RETURN_0(fp);
       
        for (int j = 0; j < event->countHeat; j++) 
        {
            SwimmingHeat* heat = &event->heatArr[j];
           
            if(!writeIntToFile(heat->type, fp))
                COLSE_RETURN_0(fp);
            
            if(!writeIntToFile(heat->numReferees, fp))
                COLSE_RETURN_0(fp);
            
            for (int k = 0; k < heat->numReferees; k++) 
            {
                Referee* referee = &heat->refereeArr[k];
                
                if(!writeStringToFile(referee->name, fp))
                    COLSE_RETURN_0(fp);
               
                if(!writeIntToFile(referee->age, fp))
                    COLSE_RETURN_0(fp);
                
                if(!writeStringToFile(referee->country, fp))
                    COLSE_RETURN_0(fp);
                
                if(!writeIntToFile(referee->refType, fp))
                    COLSE_RETURN_0(fp);
            }

            if(!writeIntToFile(heat->numOfSwimmers, fp))
                COLSE_RETURN_0(fp);
            for (int m = 0; m < heat->numOfSwimmers; m++) 
            {
                Swimmer* swimmer = heat->swimmerArr[m];
                
                if(!writeStringToFile(swimmer->name, fp)) 
                    COLSE_RETURN_0(fp);
               
                if(!writeIntToFile(swimmer->age, fp))
                    COLSE_RETURN_0(fp);
               
                if(!writeIntToFile(swimmer->bestResult, fp))
                    COLSE_RETURN_0(fp);
            }
        }
    }

    if(!writeIntToFile(competition->numOfTeams, fp))
        COLSE_RETURN_0(fp);
    for (int n = 0; n < competition->numOfTeams; n++) 
    {
        Team* team = &competition->teamArr[n];
        if(!writeStringToFile(team->country, fp))
            COLSE_RETURN_0(fp);
        
        if(!writeCharsToFile(team->countryCode,CODE_LEN + 1,fp))
            COLSE_RETURN_0(fp);
        
        if(!writeIntToFile(team->numOfMedals, fp))
            COLSE_RETURN_0(fp);
        
        if(!writeIntToFile(team->numOfChampionship, fp))
            COLSE_RETURN_0(fp);
        
        if(!writeIntToFile(team->numOfWorldRecord, fp))
            COLSE_RETURN_0(fp);

        Coach* coach = team->teamCoach;
        if (!writeStringToFile(coach->name,fp))
            COLSE_RETURN_0(fp);
       if (!writeIntToFile(coach->age, fp))
            COLSE_RETURN_0(fp);
       if (!writeIntToFile(coach->experience, fp))
           COLSE_RETURN_0(fp);
       if (!writeStringToFile(coach->country, fp))
           COLSE_RETURN_0(fp);
       if (!writeIntToFile(coach->numOfChamps, fp))
           COLSE_RETURN_0(fp);
       if(!writeIntToFile(team->swimmersCount, fp))
            COLSE_RETURN_0(fp);
        
        for (int p = 0; p < team->swimmersCount; p++) 
        {
            Swimmer* swimmer = team->teamSwimmerArr[p];
            if (!writeStringToFile(swimmer->name, fp))
                COLSE_RETURN_0(fp);
            
            if (!writeIntToFile(swimmer->age, fp))
                COLSE_RETURN_0(fp);
            
            if (!writeIntToFile(swimmer->bestResult, fp))
                COLSE_RETURN_0(fp);
            
        }
    }
    fclose(fp);
    return 1;
}

int	 writeStringToFile(const char* str, FILE* fp)
{
    int length = (int)strlen(str);
    length++;
    if (!writeIntToFile(length, fp))
        return 0;

    if (!writeCharsToFile(str, length, fp))
        return 0;
    return 1;
}

int writeIntToFile(int value, FILE* fp) 
{
    return fwrite(&value, sizeof(int), 1, fp) == 1;
}
int	 writeCharsToFile(const char* arr, int size, FILE* fp)
{
    if (fwrite(arr, sizeof(char), size, fp) != size)
    {
        return 0;
    }
    return 1;

}

int writeDoubleToFile(double value, FILE* fp) 
{
    return fwrite(&value, sizeof(double), 1, fp) == 1;
}
int readIntFromBinaryFile(FILE* fp, int* value) 
{
    return fread(value, sizeof(int), 1, fp) == 1;
}

int readDoubleFromBinaryFile(FILE* fp, double* value) 
{
    return fread(value, sizeof(double), 1, fp) == 1;
}

char* readStringFromBinaryFile(FILE* fp)
{
    char* str;
    int length;
    if (!readIntFromBinaryFile(fp,&length))
        return NULL;
    str = (char*)malloc((length) * sizeof(char));
    if (!str)
    {
        return NULL;
    }
    if (fread(str, sizeof(char), length, fp) != length)
    {
        free(str);
        return NULL;
    }
    return str;
}
int	 readCharsFromFile(char* arr, int length, FILE* fp)
{
    if (fread(arr, sizeof(char), length, fp) != length)
    {
        return 0;
    }
    return 1;
}
const char* getStyleName(int style) 
{
    static const char* styleNames[] = { "Freestyle", "Butterfly", "Backstroke", "Breaststroke" };
    return styleNames[style];
}

const char* getDistanceName(int distance) 
{
    static const char* distanceNames[] = { "50m", "100m", "200m" };
    return distanceNames[distance];
}

const char* getRefereeNameType(int type) 
{
    static const char* RefTypeStr[eNumOfRef] = { "Side", "Spingboard","Main" };
    return RefTypeStr[type];
}

const char* getHeatNameType(int type) 
{
    static const char* HeatTypeStr[eNumOfHeatType] = { "Qualifiers", "SemiFinal", "Final" };
    return HeatTypeStr[type];
}