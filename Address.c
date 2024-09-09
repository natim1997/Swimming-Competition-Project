#include<stdlib.h>
#include<stdio.h>
#include"string.h"
#include "Address.h"


void initAddress(Address* address, char* country,char* city) 
{
    if (address == NULL)
        return;

    address->country = _strdup(country);
    address->city = _strdup(city);
    if (address->country == NULL || address->city == NULL)
    {
        freeAddress(address);
    }
}


void printAddress( Address* address)
{
    if (address == NULL)
    {
        printf("No address available.\n");
        return;
    }
    printf("Country: %s\nCity: %s\n", address->country, address->city);
}

void freeAddress(Address* address) 
{
    if (address != NULL)
    {
        free(address->city);
        free(address->country);
    }
}