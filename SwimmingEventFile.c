#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"SwimmingEventFile.h"
#include"General.h"
#include"SwimmingHeat.File.h"

int readStyleFile(FILE* file, eStyle* style)
{
    if (file == NULL || style == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    myGetsF(buffer, sizeof(buffer), file);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strcmp(buffer, "Freestyle") == 0)
    {
        *style = eFreestyle;
        return 1;
    }
    else if (strcmp(buffer, "Butterfly") == 0)
    {
        *style = eButterfly;
        return 1;
    }
    else if (strcmp(buffer, "Backstroke") == 0)
    {
        *style = eBackstroke;
        return 1;
    }
    else if (strcmp(buffer, "Breaststroke") == 0)
    {
        *style = eBreaststroke;
        return 1;
    }
    return 0;
}

int readDistanceFile(FILE* file, eDistance* distance)
{
    if (file == NULL || distance == NULL)
    {
        return 0;
    }
    char buffer[MAX_STR_LEN];
    myGetsF(buffer, sizeof(buffer), file);
    buffer[strcspn(buffer, "\n")] = '\0';
    if (strcmp(buffer, "50m") == 0)
    {
        *distance = e50m;
        return 1;
    }
    else if (strcmp(buffer, "100m") == 0)
    {
        *distance = e100m;
        return 1;
    }
    else if (strcmp(buffer, "200m") == 0)
    {
        *distance = e200m;
        return 1;
    }
    return 0;
}
int readEventFromBinaryFile(FILE* file, SwimmingEvent* event) 
{
    if (fread(&event->style, sizeof(int), 1, file) != 1 ||
        fread(&event->distance, sizeof(int), 1, file) != 1 ||
        fread(&event->countHeat, sizeof(int), 1, file) != 1) {
        COLSE_RETURN_0(file);
    }

    event->heatArr = (SwimmingHeat*)malloc(sizeof(SwimmingHeat) * event->countHeat);
    for (int i = 0; i < event->countHeat; i++) 
    {
        if (!readHeatFromBinaryFile(file, &event->heatArr[i])) 
        {
            COLSE_RETURN_0(file);
        }
    }
    return 1;
}