#include<stdlib.h>
#include<stdio.h>
#include"string.h"
#include "SwimmingEvent.h"
#include"General.h"
static const char* StyleTypeStr[eNumOfStyle] = { "Freestyle", "Butterfly", "Backstroke", "Breaststroke" };

static const char* DistanceTypeStr[eNumOfDistance] = { "50m", "100m", "200m" };


int compareWorldRec(const SwimmingEvent* event1, const SwimmingEvent* event2)
{
    if (event1 == NULL || event2 == NULL)
        return 0;

    return event1->worldRecord - event2->worldRecord;
}
int compareCompetitionRec(const SwimmingEvent* event1, const SwimmingEvent* event2)
{
    if (event1 == NULL || event2 == NULL)
        return 0;

    return event1->competitionRecord - event2->competitionRecord;
}
int addHeat(SwimmingEvent* event, SwimmingHeat* heat)
{
    if (event == NULL || heat == NULL)
        return 0;

    event->heatArr = (SwimmingHeat*)realloc(event->heatArr, (event->countHeat + 1) * sizeof(SwimmingHeat));
    if (event->heatArr == NULL)
        return 0;

    event->heatArr[event->countHeat] = *heat;
    event->countHeat++;
    return 1;
}

int initEvent(SwimmingEvent* event, int worldRec, int competitionRec, eStyle style, eDistance distance)
{
    if (event == NULL)
        return 0;

    event->worldRecord = worldRec;
    event->competitionRecord = competitionRec;
    event->heatArr = NULL;
    event->countHeat = 0;
    event->style = style;
    event->distance = distance;
    return 1;
}
void freeEvent(SwimmingEvent* events, int count)
{
    if (events != NULL)
    {
        for (int i = 0; i < count; i++)
            freeHeatArr(events);

        free(events);
    }
}
void freeHeatArr(SwimmingEvent* events)
{
    for (int i = 0; i < events->countHeat; i++)
    {
        freeHeat(&events->heatArr[i]);
    }
}

void printEvent(const SwimmingEvent* event)
{
    if (event == NULL)
    {
        printf("No event to print.\n");
        return;
    }
    printf("Style: %s\nDistance: %s\n", StyleTypeStr[event->style], DistanceTypeStr[event->distance]);

}
eStyle getStyle()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following styles\n");
        for (int i = 0; i < eNumOfStyle; i++)
            printf("%d for %s\n", i, StyleTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfStyle);
    getchar();
    return (eStyle)option;
}
eDistance getDistance()
{
    int option;
    printf("\n\n");
    do {
        printf("Please enter one of the following distances\n");
        for (int i = 0; i < eNumOfDistance; i++)
            printf("%d for %s\n", i, DistanceTypeStr[i]);
        scanf("%d", &option);
    } while (option < 0 || option >= eNumOfDistance);
    getchar();
    return (eDistance)option;
}
eStyle getStyleType(char* input)
{
    printf("Enter swimming style (Freestyle, Butterfly, Backstroke, Breaststroke): ");
    scanf("%99s", input);

    for (int i = 0; i < eNumOfStyle; i++)
    {
        if (strcmp(input, StyleTypeStr[i]) == 0)
            return (eStyle)i;

    }
    printf("Invalid style. Defaulting to Freestyle.\n");
    return eFreestyle;
}
eDistance getDisType(char* input)
{
    printf("Enter swimming distance (50m, 100m, 200m): ");
    scanf("%99s", input);
    for (int i = 0; i < eNumOfDistance; i++)
    {
        if (strcmp(input, DistanceTypeStr[i]) == 0)
            return (eDistance)i;

    }
    printf("Invalid distance. Defaulting to 50m.\n");
    return e50m;
}
void printHeatsArr(SwimmingHeat* heats, int count)
{
    generalArrayFunction(heats, count, sizeof(SwimmingHeat), printHeatNew);
}
char* getEventName(SwimmingEvent* event)
{
    if (event == NULL)
        return NULL;

    const char* styleName = StyleTypeStr[event->style];
    const char* distanceName = DistanceTypeStr[event->distance];

    size_t length = strlen(styleName) + strlen(distanceName) + 2;

    char* eventName = malloc(length * sizeof(char));
    if (eventName == NULL)
        return NULL;

    snprintf(eventName, length, "%s %s", styleName, distanceName);

    return eventName;
}