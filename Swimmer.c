#include "Swimmer.h"
#include<stdlib.h>
#include<stdio.h>
#include"string.h"



int initSwimmer(Swimmer* swimmer, char* name, int age, int bestResult)
{
    if (swimmer == NULL)
    {
        return 0;
    }

    swimmer->name = _strdup(name);
    if (swimmer->name == NULL)
    {
        return 0;
    }

    swimmer->age = age;
    swimmer->bestResult = bestResult;
    return 1;
}
void printSwimmer(const Swimmer* swimmer)
{
    if (swimmer == NULL)
    {
        printf("No swimmer to print.\n");
        return;
    }
    printf("Name: %s\n, Age: %d\n, Best Result: %d\n", swimmer->name, swimmer->age, swimmer->bestResult);
}
char* getSwimmerName(Swimmer* swimmer)
{
    if (swimmer == NULL)
    {
        return NULL;
    }
    return swimmer->name;
}
void freeSwimmer(Swimmer* swimmer)
{
    if (swimmer != NULL)
        free(swimmer->name);

}