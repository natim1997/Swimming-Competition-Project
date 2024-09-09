#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include"Referee.h"

static const char* RefTypeStr[eNumOfRef] = { "Side", "Spingboard","Main" };

int initRef(Referee* ref, char* name, int age, char* country, eRefType refType)
{
    if (ref == NULL)
        return 0;

    ref->name = _strdup(name);
    ref->country = _strdup(country);
    if (ref->name == NULL || ref->country == NULL)
    {
        freeRef(ref);
        return 0;
    }
    ref->age = age;
    ref->refType = refType;
    return 1;
}
void printRef(const Referee* ref)
{
    if (ref == NULL)
    {
        printf("No referee data available.\n");
        return;
    }
    printf("Referee Name: %s\nAge: %d\nCountry: %s\n", ref->name, ref->age, ref->country);
    printf("Referee Type : %s\n", RefTypeStr[ref->refType]);
}
void freeRef(Referee* ref)
{
    if (ref != NULL)
    {
        free(ref->name);
        free(ref->country);
    }
}
eRefType getRefereeType()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following referee types\n");
        for (int i = 0; i < eNumOfRef; i++)
            printf("%d for %s\n", i, RefTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfRef);
    getchar();
    return (eRefType)option;
}