#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "SwimmingHeat.h"
#include"General.h"

static const char* HeatTypeStr[eNumOfHeatType] = { "Qualifiers", "SemiFinal", "Final" };

int initHeat(SwimmingHeat* heat, int numOfHeats, eHeatType type, Referee ref)
{
    if (heat == NULL)
        return 0;

    for (int i = 1; i <= MAX_SWIMMERS_PER_HEAT; i++)
    {
        heat->swimmerArr[i] = (Swimmer*)malloc(sizeof(Swimmer));
        if (heat->swimmerArr[i] == NULL)
            return 0;

    }
    heat->timeResultArr = (int*)malloc(numOfHeats * sizeof(int));
    if (heat->swimmerArr == NULL || heat->timeResultArr == NULL)
    {
        free(heat->swimmerArr);
        free(heat->timeResultArr);
        return 0;
    }
    heat->numOfSwimmers = 0;
    heat->counterTime = 0;
    heat->type = type;
    return 1;
}
void printHeat(const SwimmingHeat* heat)
{
    if (heat == NULL)
    {
        printf("No heat data.\n");
        return;
    }
    printf("Heat Type: %s\n", HeatTypeStr[heat->type]);
    printf("There are : %d of referees in the heat\n", heat->numReferees);

    for (int i = 0; i < NUMBER_OF_REFEREES_PER_HEAT; i++)
    {
        printf("%d - ", i + 1);
        printRef(&heat->refereeArr[i]);
    }
    printf("------------------\n");
    printf("There are : %d of swimmers in the heat\n", heat->numOfSwimmers);
    printSwimmerArr(heat->swimmerArr, heat->numOfSwimmers);
}

void freeHeat(SwimmingHeat* heat)
{
    if (heat != NULL)
    {
        freeSwimmerArr(heat->swimmerArr, heat->numOfSwimmers);
        free(heat->timeResultArr);
        freeRefArr(heat);
    }
}
int setResultToSwimmer(SwimmingHeat* heat, int swimmerIndex, int time)
{
    if (heat == NULL || swimmerIndex < 0 || swimmerIndex >= heat->numOfSwimmers)
        return 0;

    heat->timeResultArr[swimmerIndex] = time;
    return time;
}
void freeRefArr(SwimmingHeat* heat)
{
    for (int i = 0; i < heat->numReferees; i++)
    {
        freeRef(&heat->refereeArr[i]);
    }
}

void printResult(double* results, int count)
{
    if (results == NULL)
    {
        printf("No results to print.\n");
        return;
    }
    for (int i = 0; i < count; i++)
    {
        printf("Swimmer %d time: %.2f\n", i + 1, results[i]);
    }
}

void addRefereesToHeat(SwimmingHeat* heat)
{
    if (heat == NULL)
    {
        printf("Heat data is NULL.\n");
        return;
    }
    heat->refereeArr = (Referee*)malloc(MAX_REFEREES_PER_HEAT * sizeof(Referee));
    if (heat->refereeArr == NULL)
    {
        printf("Failed to allocate memory for referees.\n");
        return;
    }
    int isUniqueReferee;
    for (int i = 0; i < NUMBER_OF_REFEREES_PER_HEAT; i++)
    {
        do {
            isUniqueReferee = 1; 
            Referee newReferee;
            newReferee.name = getStrExactName("Enter referee's name:");
            printf("Enter referee's age: ");
            scanf("%d", &newReferee.age);
            getchar();
            newReferee.country = getStrExactName("Enter referee's country:");
            newReferee.refType = getRefereeType();
            for (int j = 0; j < i; j++)
            {
                if (strcmp(heat->refereeArr[j].name, newReferee.name) == 0 && heat->refereeArr[j].age == newReferee.age)
                {
                    printf("A referee with this name and age already exists in this heat. Please enter different details.\n");
                    isUniqueReferee = 0;
                    freeRef(&newReferee);
                    break;
                }
            }
            if (isUniqueReferee)
                heat->refereeArr[i] = newReferee;

        } while (!isUniqueReferee);
    }
}
eHeatType getHeatType()
{
    int option;
    printf("\n\nPlease enter one of the following heat types:\n");
    for (int i = 0; i < eNumOfHeatType; i++)
    {
        printf("%d for %s\n", i, HeatTypeStr[i]);
    }
    printf("Enter your choice: ");
    scanf("%d", &option);
    while (option < 0 || option >= eNumOfHeatType)
    {
        printf("Invalid option. Please enter a number between 0 and %d: ", eNumOfHeatType - 1);
        scanf("%d", &option);
    }
    getchar();
    return (eHeatType)option;
}
void printHeatToEvent(SwimmingHeat* heat)
{
    if (heat == NULL)
    {
        printf("No heat data.\n");
        return;
    }
    printf("Heat Type: %s\n", HeatTypeStr[heat->type]);
}
void printSwimmerArr(Swimmer** swimmers, int count)
{
    generalArrayFunction(swimmers, count, sizeof(Swimmer*), printSwimmerPtr);
}
void printSwimmerPtr(void* element)
{
    Swimmer* swimmer = *(Swimmer**)element;
    if (swimmer != NULL)
    {
        printf("Swimmer name: %s\n", swimmer->name);
        printf("Swimmer age: %d\n", swimmer->age);
        printf("Best result of the swimmer: %d\n", swimmer->bestResult);
    }
}
void freeSwimmerArr(Swimmer** swimmers, int count)
{
    generalArrayFunction(swimmers, count, sizeof(Swimmer*), freeSwimmerPtr);
    free(swimmers);
}
void freeSwimmerPtr(void* element)
{
    Swimmer* swimmer = (Swimmer*)element;
    free(swimmer);
}

void printHeatNew(void* element)
{
    printHeat((SwimmingHeat*)element);
}
void printRefNew(void* element)
{
    printRef((Referee*)element);
}
