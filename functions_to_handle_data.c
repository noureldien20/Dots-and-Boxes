#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Player 
{
    char name[50];
    int score;
}Player;


void Winner(Player *winner, int *MAX_PLAYERS) 
{
    FILE *file = fopen("player_data.bin", "rb+");

    if (file == NULL) 
    {
                                                                        // create the file if it doesn't exist
        file = fopen("player_data.bin", "wb+");
        if (file == NULL) printf("Error opening or creating the file.\n");
    }

    Player currentPlayer;
    int found = 0;

    //Search for the player in the file

    while (fread(&currentPlayer, sizeof(Player), 1, file) == 1) 
    {
        if (strcmp(currentPlayer.name, winner->name) == 0)      //strcmp compares 2 strings and return 0 if they are the same
        {
            found = 1;

            if (winner->score > currentPlayer.score)         //compare scores
            {
                currentPlayer.score = winner->score;

                fseek(file, -sizeof(Player), SEEK_CUR);     //update the score

                fwrite(&currentPlayer, sizeof(Player), 1, file);
            }
            break;
        }
    }

    if (!found) 
    {
        fseek(file, 0, SEEK_END);
        fwrite(winner, sizeof(Player), 1, file);
        (*MAX_PLAYERS)++;
    }

    fclose(file);
}

// Display the top 10 players and their scores

void printTopPlayers(int MAX_PLAYERS) 
{
    FILE *file = fopen("player_data.bin", "rb");

    if (file == NULL) printf("Error opening the file.\n");

    Player players[MAX_PLAYERS];
    int numPlayers = 0;

    // Read player data into an array of player structures
    while (numPlayers < MAX_PLAYERS) 
    {
        if(fread(&players[numPlayers], sizeof(Player), 1, file) == 1)
        {
            numPlayers++;
        }
    }

    fclose(file);

    // Sort the players
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

    int numPlayersToPrint = (numPlayers < 10) ? numPlayers : 10;

    printf("Top %d Players:\n", numPlayersToPrint);

    for (int i = 0; i < numPlayersToPrint ; i++) 
    {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }
}

int main() 
{
    int MAX_PLAYERS = 0;

    while(1)
    {
        Player winner;

        printf("enter name:");
        scanf("%s", winner.name);

        printf("enter score:");
        scanf("%d", &winner.score);

        Winner(&winner, &MAX_PLAYERS);

        printf("MAX_PLAYERS: %d\n", MAX_PLAYERS);

        printTopPlayers(MAX_PLAYERS) ;
    }
}
