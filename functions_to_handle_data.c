
//still not finished , used txt file instead of binary

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PLAYERS_TO_PRINT 10

typedef struct Player 
{
    char name[50];
    int score;
}Player;


void Winner(Player *winner) 
{
    FILE *file = fopen("player_data.txt", "a+");

    if (file == NULL) 
    {
        // create the file if it doesn't exist
        file = fopen("player_data.bin", "w+");
        if (file == NULL) printf("Error opening or creating the file.\n");
    }

    Player temp;
    int found = 0;

    //Search for the player in the file

    while (fscanf(file, "%49s %d", temp.name, &temp.score) == 2) 
    {
        if (strcmp(temp.name, winner->name) == 0) 
        {
            found = 1;

            if (winner->score > temp.score) 
            {
                temp.score = winner->score;

                fseek(file, -(49 + sizeof(int) + 2), SEEK_SET);

                fprintf(file, "%s %d\n", temp.name, temp.score);
            }
            break;
        }
    }

    if (!found) 
    {
        fprintf(file, "%s %d\n", winner->name, winner->score);
    }

    fclose(file);
}

// Display the top 10 players and their scores

void printTopPlayers() 
{
    FILE *file = fopen("player_data.txt", "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    Player *players = NULL;  // Dynamic array to store players
    int numPlayers = 0;

    // Read players from the file dynamically
    Player tempPlayer;
    while (fscanf(file, "%49s %d", tempPlayer.name, &tempPlayer.score) == 2) 
    {
        // Dynamically allocate memory for a new player
        players = realloc(players, (numPlayers + 1) * sizeof(Player));

        // Check if memory allocation is successful
        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        // Copy the temporary player data to the array
        players[numPlayers++] = tempPlayer;
        //numPlayers++;
    }

    fclose(file);

    // Sort the players based on score
    for (int i = 0; i < numPlayers - 1; i++)
    {
        for (int j = i + 1; j < numPlayers; j++) 
        {
            if (players[j].score > players[i].score) 
            {
                Player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Top %d Players:\n", numPlayers);

    int numPlayersToPrint = (numPlayers < MAX_PLAYERS_TO_PRINT) ? numPlayers : MAX_PLAYERS_TO_PRINT;

    for (int i = 0; i < numPlayersToPrint; i++) 
    {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }

    // Free dynamically allocated memory
    free(players);
}


int main() 
{
    while(1)
    {
        Player winner;

        printf("enter name:");
        scanf("%s", winner.name);

        printf("enter score:");
        scanf("%d", &winner.score);

        Winner(&winner);

        printTopPlayers();
    }
}

