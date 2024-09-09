#include <stdio.h>
#include <stdlib.h>
#include"Main.h"





void printMenu()
{
    printf("Welcome to our swimming competition managment:\n");
    printf("1. Load System From File\n");
    printf("2. Display System\n");
    printf("3. Display Subcomponents\n");
    printf("4. Add Component to system\n");
    printf("5. Sort Components\n");
    printf("6. Search Component\n");
    printf("7. Simulate random result and medal awarded\n");
    printf("8. Youngest swimmer rewared\n");
    printf("9. Exit\n");
}

void loadSystemFromFile(DirectorSwimmingCompetition* director,SwimmingCompetition* pComp)
{
    printf("Choose where do you want to load your system from:\n1- from text.\n2- from binary.\n");
    int option;
    scanf("%d", &option);
    printf("The system is loading,it will take copule of seconds\n");
    if (option == 1)
    {
        if (!loadSwimmingCompetitionFromTextFile(director, COMPETITION_TEXTFILE))
        {
            printf("Load from text file filed\n");
            return;
        }
        printf("\nLoad from text file succeeded , thank you for your patience.\n");
    }
    else if (option == 2)
    {
        if(!loadSwimmingCompetitionFromBinaryFile(director,COMPETITION_BINARYFILE))
        {
            printf("Load from binary file filed\n");
            return;
        }
        printf("\nLoad from binary file succeeded , thank you for your patience.\n");
    }
}

void displaySystem(const DirectorSwimmingCompetition* director) 
{
    if (director == NULL) 
    {
        printf("Director is NULL\n");
        return;
    }
    printf("There are : %d competitions\n", director->countCompetition);

    NODE* pNode = director->SwimmingCompetitonList.head.next;
    while (pNode != NULL) {
        SwimmingCompetition* competition = (SwimmingCompetition*)pNode->key;
        printCompetition(competition); 
        printAddress(competition->address); 
        printDate(competition->date); 
        printf("There are : %d events for this competition\n", competition->countEvent);
        for (int j = 0; j < competition->countEvent; j++) 
        {
            SwimmingEvent* event = &competition->eventArr[j];
            printf("Event %d:\n", j + 1);
            printEvent(event); 
            printf("There are : %d heats for this event\n", competition->eventArr[j].countHeat);
            for (int h = 0; h < competition->eventArr[j].countHeat; h++) 
            {
                SwimmingHeat* heat = &event->heatArr[h];
                printf("Heat %d:\n", h + 1);
                printHeatToEvent(heat);
                
            }
        }

        printf("There are : %d Teams for this competition\n", competition->numOfTeams);
        for (int k = 0; k < competition->numOfTeams; k++) 
        {
            printf("Team %d:\n", k + 1);
            printf("There are %d Swimmers in this team\n", competition->teamArr[k].swimmersCount);
            printf("There is 1 coach in this team\n");
            printf("------------------\n");
        }


        pNode = pNode->next;
    }
}

void displaySubcomponents(const DirectorSwimmingCompetition* director)
{
    if (director == NULL) 
    {
        printf("Director is NULL\n");
        return;
    }
    printf("------------------\n");
    int competitionNumber = 1;
    
    printf("There are : %d competitions\n", director->countCompetition);
    NODE* pNode = director->SwimmingCompetitonList.head.next;
    while (pNode != NULL)
    {
        SwimmingCompetition* competition = (SwimmingCompetition*)pNode->key;
        printf("Competiton %d:\n", competitionNumber);
        printCompetition(competition);  

        printAddress(competition->address);
        printDate(competition->date);
        printf("------------------\n");
        printf("There are : %d events for this competition\n", competition->countEvent);
        for (int j = 0; j < competition->countEvent; j++) 
        {
            SwimmingEvent* event = &competition->eventArr[j];
            printf("Event %d:\n", j + 1);
            printEvent(event); 
            printf("------------------\n");
            printf("There are : %d heats for this event\n",event->countHeat);
            for (int h = 0; h < event->countHeat; h++) 
            {
                SwimmingHeat* heat = &event->heatArr[h];
                printf("Heat %d)\n", h + 1);
                printHeatsArr(heat, event->countHeat);
            }
        }
        printf("------------------\n");
        printf("There are : %d Teams for this competition\n", competition->numOfTeams);
        for (int k = 0; k < competition->numOfTeams; k++) 
        {
            Team* team = &competition->teamArr[k];
            printTeam(team);  
        }
        pNode = pNode->next;
        competitionNumber++;
    }
}

void printAddComponentMenu() 
{
    printf("Choose an option to add:\n");
    printf("1. Add Swimming Competition\n");
    printf("2. Add Team\n");
    printf("3. Add Swimmer to Team\n");
    printf("4. Add Event to Competition\n");
    printf("5. Exit,for see the changes press 5 and after 3 in the main manu\n");
    printf("Choice: ");
}

void addComponent(DirectorSwimmingCompetition* director) 
{
    int choice;

    do {
        printAddComponentMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addSwimmingCompetition(director);
            break;
        case 2:
            addTeam(director);
            break;
        case 3:
            addSwimmerToTeam(director);
            break;
        case 4:
            addEventToCompetition(director);
            break;
        case 5:
            printf("Exit.\n");
            break;
        default:
            printf("Invalid choice,Please try again.\n");
        }
    } while (choice != 5);
}

void PrintSortMenu() 
{
    printf("Choose a component to sort:\n");
    printf("1. Sort Teams\n");
    printf("2. Exit to main menu,for see the changes press 3 in the main menu\n");
}

void sortComponents(SwimmingCompetition* competition)//need to add DirectorSwimmingCompetition* and count;
{
    PrintSortMenu();
    int choice;
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        if (isTeamAvailable(competition))
        {
            sortTeams(competition->teamArr,competition->numOfTeams);
        }
        else {
            printf("No teams available to sort.\n");
        }
        break;
    case 2:
        printf("Back to the main manu.\n");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }
}
void PrintFindMenu()
{
    printf("Choose a component to find:\n");
    printf("1. Find Teams\n");
    printf("2. Exit to main menu,for see the changes press 3 in the main menu\n");
}

void searchComponent(SwimmingCompetition* competition)
{
    PrintFindMenu();
    int choice;
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        if (isTeamAvailable(competition))
        {
            showTeamList(competition->teamArr, competition->numOfTeams);
            findTeam(competition->teamArr, competition->numOfTeams);
        }
        else {
            printf("No teams available to find.\n");
        }
        break;
    case 2:
        printf("Back to the main manu.\n");
        break;
    default:
        printf("Invalid choice.\n");
        break;
    }

}


int saveSystemToFile(DirectorSwimmingCompetition* director) 
{
    if (!saveCompetitionToTextFile(director,(SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key, COMPETITION_TEXTFILE))
    {
        printf("Failed to save competition to text file.\n");
        return 0;
    }
    else
        printf("Succeeded to save competition to text file.\n");
    if (!saveCompetitionToBinaryFile(director,(SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key, COMPETITION_BINARYFILE))
    {
        printf("Failed to save competition to binary file.\n");
        return 0;
    }
    else
        printf("Succeeded to save competition to binary file.\n");
    return 1;
}

int main() 
{
    int choice;
    DirectorSwimmingCompetition* director = initDirector();
    if (!director) 
    {
        printf("Failed to initialize the director.\n");
        return 0;
    }
    SwimmingCompetition* pComp = initCompetition();
    if(pComp == NULL) 
    {
        printf("Failed to init SwimmingCompetition.\n");
        return 0;
    }
    /*Team* team = initTeamToCompetition();
    if (team == NULL)
    {
        printf("Failed to init Team.\n");
        return 0;
    }*/
    do 
    {
        printMenu();
        printf("\n");
        printf("Enter your choice: \n");
        scanf("%d", &choice);

        switch (choice) 
        {
        case 1:   
            loadSystemFromFile(director, pComp);
            break;
        case 2: 
            if (isDataAvailable(director))
            {
                displaySystem(director);
            }
            else
                printf("No competition data available. Please load or create a competition first.\n");
            break;
        case 3:
            if (isDataAvailable(director))
            {
                displaySubcomponents(director);
            }
            else
                printf("No competition data available. Please load or create a competition first.\n");
            break;
        case 4:
            if (isDataAvailable(director)) 
            {
                addComponent(director);
            }
            else 
                printf("No competition data available. Please load or create a competition first.\n");            
            break;
        case 5: 
            sortComponents((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key);
            break;
        case 6: 
            searchComponent((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key);
            break;
        case 7:
            if (isDataAvailable(director))
            {
                simulateAndSortHeat((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key, ((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key)->eventArr, ((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key)->eventArr->heatArr);
            }
            else
                printf("No competition data available. Please load or create a competition first.\n");
            break;
        case 8:
            if (isDataAvailable(director))
            {
                awardYoungestSwimmer((SwimmingCompetition*)director->SwimmingCompetitonList.head.next->key);
            }
            else
                printf("No competition data available. Please load or create a competition first.\n");
            break;
        case 9: 
            printf("Exiting.\nThank you for compete in our Swimming Competition see you next time , bye bye. \n");
            break;
        default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 9);
    saveSystemToFile(director);
    //savetotext 
   /* free(pComp);
    freeDirector(director);*/
    return 1;
}

// Implementations for the functions
// ...
