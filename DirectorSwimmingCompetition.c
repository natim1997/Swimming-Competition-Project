#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include "DirectorSwimmingCompetition.h"
#include "SwimmingCompetition.h"
#include"General.h"
#include "SwimmingEvent.h"



DirectorSwimmingCompetition* initDirector() 
{
    DirectorSwimmingCompetition* director = malloc(sizeof(DirectorSwimmingCompetition));
    if (director != NULL) {
        if (!L_init(&(director->SwimmingCompetitonList))) 
        {
            freeDirector(director);
            return NULL;
        }
        director->countCompetition = 0;
    }
    return director;
}


int addSwimmingCompetition(DirectorSwimmingCompetition* director)
{
    if (director == NULL) 
    {
        printf("Director data is NULL.\n");
        return 0;
    }
    char* name;
    int isUniqueName; 
    do 
    {
        name = getStrExactName("Enter competition name:\n");
        isUniqueName = 1; 

        NODE* pNode = director->SwimmingCompetitonList.head.next;
        while (pNode != NULL) 
        {
            SwimmingCompetition* competition = (SwimmingCompetition*)pNode->key;
            if (strcmp(name, competition->competitionName) == 0) 
            {
                isUniqueName = 0;
                printf("This competition name already exists. Please enter a different name.\n");
                free(name);
                break;
            }
            pNode = pNode->next;
        }
    } while (!isUniqueName);
    
    char* country = getStrExactName("Enter country of competition:\n");
    char* city = getStrExactName("Enter city of competition:\n");

    Date dateInput;
    getDateInput(&dateInput);

    SwimmingCompetition* newCompetition = (SwimmingCompetition*)malloc(sizeof(SwimmingCompetition));
    if (!newCompetition) 
    {
        printf("Memory allocation failed for new competition.\n");
        return 0;
    }
    Address* address = (Address*)malloc(sizeof(Address));
    if (!address)
    {
        free(name);
        free(country);
        free(city);
        free(newCompetition);
        printf("Failed to allocate memory for address.\n");
        return 0;
    }
    address->country = country;
    address->city = city;

    Date* compDate = (Date*)malloc(sizeof(Date));
    if (!compDate)
    {
        free(name);
        free(country);
        free(city);
        free(address);
        free(newCompetition);
        printf("Failed to allocate memory for date.\n");
        return 0;
    }
    *compDate = dateInput;

    if (!initSwimmingCompetition(newCompetition, name, country,address, compDate)) 
    {
        freeCompetition(newCompetition);
        return 0;
    }
    newCompetition->address = address;
    newCompetition->date = compDate;
    
    int addEventChoice;
    do {
        printf("Do you want to add an event to the competition? Enter 1 for Yes, 0 for No: \n");
        scanf("%d", &addEventChoice);
        if (addEventChoice == 1)
        {
            addEventToCompetition(director);
        }
    } while (addEventChoice != 0);

    if (L_insert(&(director->SwimmingCompetitonList.head), newCompetition) == NULL) 
    {
        freeCompetition(newCompetition);
        return 0;
    }
    director->countCompetition++;
    return 1;
}

int initSwimmingCompetition(SwimmingCompetition* competition,const char* name, const char* country, Address* address, Date* date)  
  {
    
    competition->competitionName = _strdup(name);
    competition->address = address;
    competition->date = date;
    competition->eventArr = NULL;
    competition->countEvent = 0;
    competition->numOfTeams = 0;
    competition->teamArr = NULL;
    return 1;
}

SwimmingCompetition* initCompetition()
{
    SwimmingCompetition* competition = (SwimmingCompetition*)malloc(sizeof(SwimmingCompetition));
    if (!competition)
    {
        printf("Failed to allocate memory for SwimmingCompetition.\n");
        return NULL;
    }
    competition->competitionName = NULL;
    competition->address = NULL;
    competition->date = NULL;
    competition->eventArr = NULL;
    competition->countEvent = 0;
    competition->numOfTeams = 0;
    competition->teamArr = NULL;
    return competition;
}

void freeDirector(DirectorSwimmingCompetition* director)
{
    if (director != NULL)
    {
        L_free(&(director->SwimmingCompetitonList), freeCompetition);
        free(director);
    }
}

void printCompetitionArr(const DirectorSwimmingCompetition* director)
{
    if (director != NULL)
    {
        L_print(&(director->SwimmingCompetitonList), printCompetition);
    }
}

int isDataAvailable(const DirectorSwimmingCompetition* director) 
{
    return (director != NULL && director->countCompetition > 0);
}

SwimmingCompetition* chooseCompetition(DirectorSwimmingCompetition* director) 
{
    if (director == NULL || director->SwimmingCompetitonList.head.next == NULL) 
    {
        printf("No competitions available.\n");
        return NULL;
    }

    printf("Available Competitions:\n");
    int index = 1;
    NODE* pNode = director->SwimmingCompetitonList.head.next;
    
    while (pNode != NULL) 
    {
        SwimmingCompetition* comp = (SwimmingCompetition*)pNode->key;
        printf("%d. %s\n", index, comp->competitionName);
        pNode = pNode->next;
        index++;
    }

    printf("Select a competition (enter the number): ");
    int choice;
    scanf("%d", &choice);
    getchar(); 

    if (choice < 1 || choice >= index) 
    {
        printf("Invalid choice.\n");
        return NULL;
    }

    pNode = director->SwimmingCompetitonList.head.next;
    for (int i = 1; i < choice; i++)
        pNode = pNode->next;
   
    return (SwimmingCompetition*)pNode->key;
}
void addTeam(DirectorSwimmingCompetition* director)
{
    SwimmingCompetition* selectedCompetition = chooseCompetition(director);
    if (selectedCompetition == NULL) {
        printf("No competition selected.\n");
        return;
    }
    char* country = NULL;
    char* countryCode;
    
    country = getUniqueCountryName(selectedCompetition);
    
    countryCode = getUniqueCountryCode(selectedCompetition);
    
    Team newTeam;    
    if (!initTeam(&newTeam, country, countryCode))
        return;
   
    printf("Enter the number of medals won by the team: ");
    scanf("%d", &newTeam.numOfMedals);
    printf("Enter the number of championships won by the team: ");
    scanf("%d", &newTeam.numOfChampionship);
    printf("Enter the number of world records held by the team: ");
    scanf("%d", &newTeam.numOfWorldRecord);
    
    Coach* coach = createUniqueCoach(selectedCompetition);
    if(!initCoach(coach,coach->name,coach->age))
        return;
    coach->country = getStrExactName("Enter coach's country:");
    printf("Enter coach's experience in years:\n ");
    scanf("%d", &coach->experience);
    printf("Enter the number of championships won by coach:\n");
    scanf("%d", &coach->numOfChamps);
    
    newTeam.teamCoach = coach;
    addTeamToCompetition(selectedCompetition, &newTeam);
}
void addSwimmerToTeam(DirectorSwimmingCompetition* director) 
{
    SwimmingCompetition* chosenComp = chooseCompetition(director);
    if (chosenComp == NULL) 
    {
        printf("No competition selected or invalid competition.\n");
        return;
    }
    if (chosenComp->numOfTeams == 0) 
    {
        printf("No teams available in this competition. Please add a team first.\n");
        return;
    }
    for (int i = 0; i < chosenComp->numOfTeams; i++) 
    {
        printf("%d. %s\n", i + 1, chosenComp->teamArr[i].country);
    }
    printf("Choose a team number: ");
    int teamChoice;
    scanf("%d", &teamChoice);
    getchar(); 

    if (teamChoice < 1 || teamChoice > chosenComp->numOfTeams) 
    {
        printf("Invalid team choice.\n");
        return;
    }

    Team* selectedTeam = &(chosenComp->teamArr[teamChoice - 1]);
    
    int isUnique;
    char* swimmerName;
    int swimmerAge;
    do {
        isUnique = 1; 
        swimmerName = getStrExactName("Enter swimmer's name:\n");
        printf("Enter swimmer's age: \n");
        scanf("%d", &swimmerAge);
        getchar(); 

        for (int i = 0; i < selectedTeam->swimmersCount; i++) 
        {
            if (strcmp(selectedTeam->teamSwimmerArr[i]->name, swimmerName) == 0 && selectedTeam->teamSwimmerArr[i]->age == swimmerAge) 
            {
                printf("A swimmer with this name and age already exists in the team. Please enter different details.\n");
                isUnique = 0;
                free(swimmerName);
                break;
            }
        }
    } while (!isUnique);
    
   
    Swimmer newSwimmer;
    newSwimmer.name = swimmerName;
    newSwimmer.age = swimmerAge;

    printf("Enter swimmer's best result: ");
    scanf("%d", &newSwimmer.bestResult);

    addSwimmerToTeamArray(selectedTeam, &newSwimmer);
}

void addSwimmerToTeamArray(Team* team, Swimmer* newSwimmer)
{
    if (team->swimmersCount == team->capacity)
    {
        int newCapacity = team->capacity == 0 ? 2 : team->capacity * 2;
        Swimmer** temp = (Swimmer**)realloc(team->teamSwimmerArr, newCapacity * sizeof(Swimmer*)); 
        if (!temp)
        {
            printf("Failed to allocate memory for swimmers.\n");
            return;
        }
        team->teamSwimmerArr = temp;
        team->capacity = newCapacity;
    }
    Swimmer* swimmerCopy = (Swimmer*)malloc(sizeof(Swimmer));
    if (!swimmerCopy) {
        printf("Failed to allocate memory for new swimmer.\n");
        return;
    }
    *swimmerCopy = *newSwimmer; 
    team->teamSwimmerArr[team->swimmersCount++] = swimmerCopy;
}
void addEventToCompetition(DirectorSwimmingCompetition* director) 
{
    if (director == NULL)
    {
        printf("Competition data is NULL.\n");
        return;
    }
    SwimmingCompetition* selectedCompetition = chooseCompetition(director);
    if (selectedCompetition == NULL) 
    {
        printf("No competition selected.\n");
        return;
    }
    SwimmingEvent newEvent;
    newEvent.style = getStyle();
    newEvent.distance = getDistance();
    newEvent.worldRecord = 0;
    newEvent.competitionRecord = 0;
    int numHeats;
    printf("Enter the number of heats for this event: ");
    scanf("%d", &numHeats);
    getchar(); 
    printf("Every heat has 3 referees and 8 swimmers.\n");
    newEvent.heatArr = (SwimmingHeat*)malloc(numHeats * sizeof(SwimmingHeat));
    if (newEvent.heatArr == NULL) 
    {
        printf("Failed to allocate memory for heats.\n");
        return;
    }
    newEvent.countHeat = 0;
  
    for (int i = 0; i < numHeats; i++) 
    {
        printf("Adding heat %d:\n", i + 1);
        SwimmingHeat* heat = &newEvent.heatArr[i];
        addHeatToEvent(selectedCompetition,&newEvent);
    }
    addEventToCompetitionArray(selectedCompetition, &newEvent);
}
void addEventToCompetitionArray(SwimmingCompetition* competition, SwimmingEvent* newEvent) 
{
    if (competition == NULL || newEvent == NULL) 
    {
        printf("Invalid input.\n");
        return;
    }
    SwimmingEvent* temp = realloc(competition->eventArr,
        (competition->countEvent + 1) * sizeof(SwimmingEvent));
    if (temp == NULL) 
    {
        printf("Failed to reallocate memory for events.\n");
        return;
    }

    competition->eventArr = temp;
    competition->eventArr[competition->countEvent] = *newEvent;
    competition->countEvent++;
}
char* getUniqueCountryName(SwimmingCompetition* selectedCompetition) 
{
    int isUnique;
    char* country;

    do {
        isUnique = 1;
        country = getStrExactName("Enter team's country name:");

        for (int i = 0; i < selectedCompetition->numOfTeams; i++) 
        {
            if (strcmp(selectedCompetition->teamArr[i].country, country) == 0) 
            {
                printf("This country name already exists in this competition. Please enter a different name.\n");
                isUnique = 0;
                free(country);
                break;
            }
        }
    } while (!isUnique);

    return country;
}
char* getUniqueCountryCode(SwimmingCompetition* selectedCompetition) 
{
    int isUnique;
    char countryCode[CODE_LEN + 1];

    do {
        isUnique = 1;
        getCountryCode(countryCode);

        for (int i = 0; i < selectedCompetition->numOfTeams; i++) 
        {
            if (strcmp(selectedCompetition->teamArr[i].countryCode, countryCode) == 0) 
            {
                printf("This country code already exists in this competition. Please enter a different code.\n");
                isUnique = 0;
                break;
            }
        }
    } while (!isUnique);

    char* uniqueCountryCode = strdup(countryCode);
    if (uniqueCountryCode == NULL) {
        printf("Failed to allocate memory for unique country code.\n");
        return NULL;
    }

    return uniqueCountryCode;
}
Coach* createUniqueCoach(SwimmingCompetition* selectedCompetition) 
{
    int isUniqueCoach;
    Coach* coach = NULL;

    do {
        isUniqueCoach = 1; 
        coach = (Coach*)malloc(sizeof(Coach));
        if (coach == NULL) 
        {
            printf("Failed to allocate memory for coach.\n");
            return NULL;
        }

        coach->name = getStrExactName("Enter coach's name:");
        printf("Enter coach's age: ");
        scanf("%d", &coach->age);
        getchar(); 

        for (int i = 0; i < selectedCompetition->numOfTeams; i++)
        {
            if (selectedCompetition->teamArr[i].teamCoach && strcmp(selectedCompetition->teamArr[i].teamCoach->name, coach->name) == 0 && selectedCompetition->teamArr[i].teamCoach->age == coach->age)
            {
                printf("A coach with this name and age already exists in a team. Please enter different details.\n");
                isUniqueCoach = 0;
                free(coach->name);
                free(coach); 
                coach = NULL; 
                break;
            }
        }
    } while (!isUniqueCoach);

    return coach;
}
