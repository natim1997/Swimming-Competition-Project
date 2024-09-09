#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<ctype.h>
#include<time.h>
#include"General.h"
#include "SwimmingCompetition.h"

static const char* teamSortOptStr[] = { "Number of Championships", "Number of World Records", "Country" };


void getCompetition(SwimmingCompetition* competition)
{
    if (competition == NULL)
    {
        printf("No competition data available.\n");
        return;
    }
    printf("Competition Name: %s\n", competition->competitionName);
}


int isSameCompetition(SwimmingCompetition* comp1, SwimmingCompetition* comp2)
{
    if (comp1 == NULL || comp2 == NULL)
    {
        return 0;
    }
    return strcmp(comp1->competitionName, comp2->competitionName) == 0;   
}


void freeCompetition(SwimmingCompetition* competition)
{
    if (competition != NULL)
    {
        free(competition->competitionName);
        free(competition->date);
        freeEventArr(competition);
        freeTeamArr(competition);
        freeAddress(competition->address);
        free(competition);
    }
}


void printCompetition(SwimmingCompetition* competition)
{
    if (competition == NULL)
    {
        printf("No competition to print.\n");
        return;
    }
    printf("Competition Name: %s\n", competition->competitionName);
}


void printEvents(SwimmingEvent* events, int count)
{
    if (events == NULL)
    {
        printf("No events to print.\n");
        return;
    }
    for (int i = 0; i < count; i++) 
    {
        printf("Event %d: [Details here]\n", i + 1);
    }
}


void freeEventArr(SwimmingCompetition* competition)
{
    freeEvent(competition->eventArr, competition->countEvent);
}
void freeTeamArr(SwimmingCompetition* competition)
{
    freeTeam(competition->teamArr,competition->numOfTeams);   
}


void getCode(char* code) 
{
    char temp[CODE_LEN + 1]; // +1 for null terminator
    int ok = 1;
    do {
        ok = 1;
        printf("Enter team's country code - %d UPPER CASE letters\t", CODE_LEN);
        myGets(temp, sizeof(temp), stdin);
        if (strlen(temp) != CODE_LEN) {
            printf("Code should be %d letters\n", CODE_LEN);
            ok = 0;
        }
        else 
        {
            for (int i = 0; i < CODE_LEN; i++) 
            {
                if (!isupper(temp[i])) 
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
void addTeamToCompetition(SwimmingCompetition* competition, Team* newTeam) 
{
    if (competition == NULL || newTeam == NULL) 
    {
        printf("Invalid arguments to addTeamToCompetition.\n");
        return;
    }
    if (competition->teamArr == NULL) 
    {        
        competition->teamArr = (Team*)malloc(sizeof(Team));
        if (competition->teamArr == NULL) 
        {
            printf("Failed to allocate memory for teams.\n");
            return;
        }
        competition->numOfTeams = 0;
    }
    else 
    {    
        Team* temp = (Team*)realloc(competition->teamArr,(competition->numOfTeams + 1) * sizeof(Team));
        if (temp == NULL) 
        {
            printf("Failed to reallocate memory for teams.\n");
            return;
        }
        competition->teamArr = temp;
    }
    competition->teamArr[competition->numOfTeams] = *newTeam;
    competition->numOfTeams++;
}

int compareTeamByChampionships(const void* a, const void* b) 
{
    const Team* teamA = (const Team*)a;
    const Team* teamB = (const Team*)b;
    return teamB->numOfChampionship - teamA->numOfChampionship;
}

int compareTeamByWorldRecords(const void* a, const void* b) 
{
    const Team* teamA = (const Team*)a;
    const Team* teamB = (const Team*)b;
    return teamB->numOfWorldRecord - teamA->numOfWorldRecord;
}

int compareTeamByCountry(const void* a, const void* b) 
{
    const Team* teamA = (const Team*)a;
    const Team* teamB = (const Team*)b;
    return strcmp(teamA->country, teamB->country);
}
eTeamSortOption showTeamSortMenu() 
{
    int opt;
    printf("Teams based on:\n");
    do {
        for (int i = 0; i < eTeamNofSortOpt; i++)
            printf("Enter %d for %s\n", i, teamSortOptStr[i]);
        scanf("%d", &opt);
    } while (opt < 0 || opt >= eTeamNofSortOpt);

    return (eTeamSortOption)opt;
}

void sortTeams(Team* teams, int teamCount) 
{
    eTeamSortOption sortOption = showTeamSortMenu();
    int (*compare)(const void*, const void*) = NULL;

    switch (sortOption) {
    case eNumOfChampionships:
        compare = compareTeamByChampionships;
        break;
    case eNumOfWorldRecords:
        compare = compareTeamByWorldRecords;
        break;
    case eCountry:
        compare = compareTeamByCountry;
        break;
    }

    if (compare != NULL)
    {
        qsort(teams, teamCount, sizeof(Team), compare);
        printf("The Teams were sorted,for see the changes press 3 in the main manu.\n");
    }
        
        
}
int isTeamAvailable(SwimmingCompetition* competition)
{
    return (competition != NULL && competition->numOfTeams > 0);
}

void findTeam(const Team* teams, int teamCount) 
{
    eTeamSortOption findOption = showTeamSortMenu();
    Team key = {0};
    Team* foundTeam = &key;
    switch (findOption) {
    case eNumOfChampionships:
        printf("Enter the number of championships to search for: ");
        scanf("%d", &key.numOfChampionship);
        foundTeam = (Team*)bsearch(&key, teams, teamCount, sizeof(Team), compareTeamByChampionships);
        break;
    case eNumOfWorldRecords:
        printf("Enter the number of world records to search for: ");
        scanf("%d", &key.numOfWorldRecord);
        foundTeam = (Team*)bsearch(&key, teams, teamCount, sizeof(Team), compareTeamByWorldRecords);
        break;
    case eCountry:
        printf("Enter the country name to search for: ");
        scanf("%s", key.country);
        foundTeam = (Team*)bsearch(&key, teams, teamCount, sizeof(Team), compareTeamByCountry);
        break;
    }

    if (foundTeam) 
    {
        printf("Team found:\n");
        printf("Country: %s\n", foundTeam->country);
        printf("Country Code: %s\n", foundTeam->countryCode);
        printf("Number of Championships: %d\n", foundTeam->numOfChampionship);
        printf("Number of World Records: %d\n\n", foundTeam->numOfWorldRecord);
    }
    else 
    {
        printf("Team not found.\n");
    }
}
void showTeamList(const Team* teams, int teamCount) 
{
    printf("List of Teams:\n");
    printf("-----------------------------------------------------------\n");
    printf("%-20s %-10s %-10s %-10s %-10s\n", "Country", "Code", "Medals", "Championships", "World Records");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < teamCount; ++i) 
    {
        printf("%-20s %-10s %-10d %-10d %-10d\n",
            teams[i].country,
            teams[i].countryCode,
            teams[i].numOfMedals,
            teams[i].numOfChampionship,
            teams[i].numOfWorldRecord);
    }

    printf("-----------------------------------------------------------\n");
}
void addHeatToEvent(SwimmingCompetition* competition, SwimmingEvent* event) 
{
    if (event == NULL) 
    {
        printf("Event data is NULL.\n");
        return;
    }

    SwimmingHeat* temp = (SwimmingHeat*)realloc(event->heatArr, (event->countHeat + 1) * sizeof(SwimmingHeat));
    if (temp == NULL) 
    {
        printf("Failed to reallocate memory for heats.\n");
        event->countHeat--;
        return;
    }

    event->heatArr = temp;
    SwimmingHeat* newHeat = &event->heatArr[event->countHeat]; 

    newHeat->numOfSwimmers = MAX_SWIMMERS_PER_HEAT;
    newHeat->numReferees = NUMBER_OF_REFEREES_PER_HEAT;
    newHeat->type = getHeatType();
    newHeat->timeResultArr = (int*)malloc(MAX_SWIMMERS_PER_HEAT * sizeof(int)); 
    newHeat->counterTime = 0;

    addRefereesToHeat(newHeat);
    addSwimmersToHeat(competition, newHeat);

    event->countHeat++;
}
void addSwimmersToHeat(SwimmingCompetition* competition, SwimmingHeat* heat) 
{
    if (heat == NULL || competition == NULL) 
    {
        printf("Heat or competition data is NULL.\n");
        return;
    }
    Swimmer** selectedSwimmers = (Swimmer**)malloc(MAX_SWIMMERS_PER_HEAT * sizeof(Swimmer*));
    if (selectedSwimmers == NULL) 
    {
        printf("Failed to allocate memory for selected swimmers.\n");
        return;
    }
    int selectedSwimmerCount = 0;

    for (int i = 0; i < competition->numOfTeams; i++) 
    {
        Team* team = &competition->teamArr[i];
        printf("Team %s:\n", team->country);
        for (int j = 0; j < team->swimmersCount; j++) 
        {
            printf("\t%d. %s, Age: %d\n", j + 1, team->teamSwimmerArr[j]->name, team->teamSwimmerArr[j]->age);
        }
    }

    while (selectedSwimmerCount < MAX_SWIMMERS_PER_HEAT) 
    {
        printf("Select swimmer %d by entering their name and age:\n", selectedSwimmerCount + 1);
        char* swimmerName = getStrExactName("Enter swimmer's name:");
        int swimmerAge;
        printf("Enter swimmer's age: ");
        scanf("%d", &swimmerAge);

        int found = 0;
        for (int j = 0; j < competition->numOfTeams && !found; j++) 
        {
            Team* team = &competition->teamArr[j];
            for (int k = 0; k < team->swimmersCount; k++) 
            {
                if (strcmp(team->teamSwimmerArr[k]->name, swimmerName) == 0 && team->teamSwimmerArr[k]->age == swimmerAge) 
                {
                    // Check if this swimmer is already selected
                    int alreadySelected = 0;
                    for (int l = 0; l < selectedSwimmerCount; l++) 
                    {
                        if (selectedSwimmers[l] == team->teamSwimmerArr[k]) 
                        {
                            alreadySelected = 1;
                            break;
                        }
                    }
                    if (alreadySelected) 
                    {
                        printf("This swimmer has already been selected for the heat.\n");
                    }
                    else 
                    {
                        selectedSwimmers[selectedSwimmerCount++] = team->teamSwimmerArr[k];
                        found = 1;
                    }
                    break;
                }
            }
        }
        if (!found) 
        {
            printf("Swimmer not found in any team or already in another heat. Please try again.\n");
        }
    }

    heat->swimmerArr = selectedSwimmers;
    heat->numOfSwimmers = MAX_SWIMMERS_PER_HEAT;
}
int isSwimmerInOtherHeats(SwimmingCompetition* competition, Swimmer* swimmer, int currentHeatIndex) 
{
    for (int i = 0; i < competition->countEvent; i++) 
    {
        SwimmingEvent* event = &competition->eventArr[i];
        for (int j = 0; j < event->countHeat; j++) 
        {
            if (j != currentHeatIndex) 
            {
                SwimmingHeat* heat = &event->heatArr[j];
                for (int k = 0; k < heat->numOfSwimmers; k++) 
                {
                    if (heat->swimmerArr[k] == swimmer) 
                    {
                        return 1; // Swimmer found in another heat
                    }
                }
            }
        }
    }
    return 0; 
}
void simulateAndSortHeat(SwimmingCompetition* competition, SwimmingEvent* event, SwimmingHeat* heat) 
{
    srand((unsigned int)time(NULL));
    if (!heat || !competition || !event) 
    {
        printf("Invalid data provided.\n");
        return;
    }
    heat->timeResultArr = (int*)malloc(heat->numOfSwimmers * sizeof(int));
    if (!heat->timeResultArr) {
        printf("Failed to allocate memory for time results.\n");
        return;
    }
    int worldRecord = 50; // Placeholder value

    for (int i = 0; i < heat->numOfSwimmers; i++) 
    {
        int minTime = worldRecord - 2; // 1 second faster than the world record
        int maxTime = worldRecord + 20; // 15 seconds slower than the world record
        int range = maxTime - minTime + 1 ; 
        heat->timeResultArr[i] = minTime + rand() % range;
    }
    for (int i = 0; i < heat->numOfSwimmers - 1; i++) 
    {
        for (int j = i + 1; j < heat->numOfSwimmers; j++) 
        {
            if (heat->timeResultArr[i] > heat->timeResultArr[j]) 
            {
                // Swap times
                int tempTime = heat->timeResultArr[i];
                heat->timeResultArr[i] = heat->timeResultArr[j];
                heat->timeResultArr[j] = tempTime;

                // Swap swimmers
                Swimmer* tempSwimmer = heat->swimmerArr[i];
                heat->swimmerArr[i] = heat->swimmerArr[j];
                heat->swimmerArr[j] = tempSwimmer;
            }
        }
    }

    const char* medals[] = { "Gold", "Silver", "Bronze" };
    for (int i = 0; i < 3 && i < heat->numOfSwimmers; i++) 
    {
        Team* team = findSwimmerTeam(competition, heat->swimmerArr[i]);
        if (team)
        {
            printf("%s won %s medal with a time of %d seconds.\n\n", heat->swimmerArr[i]->name, medals[i], heat->timeResultArr[i]);
            team->numOfMedals++;
        }
        else
            printf("Failed to find team for swimmer %s.\n", heat->swimmerArr[i]->name);    
    }
    free(heat->timeResultArr);
}

Team* findSwimmerTeam(SwimmingCompetition* competition, Swimmer* swimmer) 
{
    for (int i = 0; i < competition->numOfTeams; i++) 
    {
        Team* team = &competition->teamArr[i];
        for (int j = 0; j < team->swimmersCount; j++) 
        {
            if (strcmp(team->teamSwimmerArr[j]->name, swimmer->name) == 0) 
            {
                return team;
            }
        }
    }
    return NULL; 
}
void awardYoungestSwimmer(SwimmingCompetition* competition) 
{
    if (competition == NULL || competition->numOfTeams == 0) 
    {
        printf("No data available to evaluate.\n");
        return ;
    }
    Swimmer* youngestSwimmer = NULL;
    int minAge = INT_MAX;
    for (int i = 0; i < competition->numOfTeams; i++) 
    {
        Team* team = &competition->teamArr[i];
        for (int j = 0; j < team->swimmersCount; j++) 
        {
            Swimmer* swimmer = team->teamSwimmerArr[j];
            if (swimmer->age < minAge) 
            {
                minAge = swimmer->age;
                youngestSwimmer = swimmer;
            }
        }
    }
    if (youngestSwimmer != NULL) 
    {
        printf("Special recognition awarded to the youngest swimmer:\n %s, Age: %d\n",
            youngestSwimmer->name, youngestSwimmer->age);
    }
    else 
    {
        printf("No swimmers found to award.\n");
    }
}