#ifndef SAVE_LOAD_H
#define SAVE_LOAD_H

#include "Basic_Var_and_Func.h"
#include "Display.h"

FILE* file;

player* loadPlayers(int* numPlayers) 
{
    FILE* file = fopen("player_data.bin", "rb");

    if (file == NULL) 
    {
        printf("File not found. Creating a new file.\n");

        // Create a new file if it doesn't exist
        file = fopen("player_data.bin", "wb");
        
        if (file == NULL) 
        {
            printf("Error creating the file.\n");
            return NULL;
        }

        fclose(file);

        // Now attempt to open the file again
        file = fopen("player_data.bin", "rb");

        if (file == NULL) 
        {
            printf("Error opening the file.\n");
            return NULL;
        }
    }

    player* players = NULL;
    *numPlayers = 0;

    player tempPlayer;

    while (fread(&tempPlayer, sizeof(player), 1, file) == 1) 
    {
        players = realloc(players, (*numPlayers + 1) * sizeof(player));

        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return NULL;
        }

        players[(*numPlayers)++] = tempPlayer;
    }

    fclose(file);

    return players;
}

void Winner(player* winner) 
{
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    int found = 0;

    // Search for the player in the array
    for (int i = 0; i < numPlayers; i++) 
    {
        if (strcmp(players[i].name, winner->name) == 0) 
        {
            found = 1;

            if (winner->score > players[i].score) 
            {
                players[i].score = winner->score;
            }
            break;
        }
    }

    if (!found) 
    {
        // Add the winner to the array
        players = realloc(players, (numPlayers + 1) * sizeof(player));

        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            return;
        }

        players[numPlayers++] = *winner;
    }

    // Save the updated players to the file
    FILE* file = fopen("player_data.bin", "wb");
    if (file != NULL) 
    {
        fwrite(players, sizeof(player), numPlayers, file);
        fclose(file);
    } 
    else 
    {
        printf("Error opening the file for saving.\n");
    }

    // Free dynamically allocated memory
    free(players);
}

// Function to serialize and save the game to a binary file
/*int saveGame(game* gamePtr) 
{
    copy_current_game_arrays_from_Ahmed();

    file = fopen("saved_game.bin", "wb");
    if (file != NULL) 
    {
        // Serialize the game struct
        fwrite(gamePtr, sizeof(game), 1, file);
        fclose(file);
        printf("Game saved successfully.\n");
        return 1;
    }
    else 
    {
        fprintf(stderr, "Unable to open file for saving.\n");
        return 0;
    }
}

// Function to deserialize and load the game from a binary file
void loadGame(game* gamePtr) 
{
    file = fopen("saved_game.bin", "rb");
    if (file != NULL) 
    {
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Deserialize the game struct
        char* buffer = (char*)malloc(fileSize);
        fread(buffer, fileSize, 1, file);
        memcpy(gamePtr, buffer, sizeof(game));
        free(buffer);

        fclose(file);
        printf("Game loaded successfully.\n");
    } 
    else 
    {
        fprintf(stderr, "Unable to open file for loading.\n");
    }
}*/

void saveGame(game* gamePtr) 
{
    copy_current_game_arrays_from_Ahmed();

    char filepath[20];
    char * filename;
    char * temp;

    printf("Enter the name of the file to be saved [MAX 20]: ");

    temp = take_input(25);

    filename = (char*)malloc(strlen(temp) + 1);

    strcpy(filename, temp);
    strcpy(filepath, "Saved Games/");
    strcat(filepath, filename);
    strcat(filepath,".bin\"");

    file = fopen(filepath, "ab");
    if (file != NULL) 
    {
        // Serialize the game struct
        fwrite(gamePtr, sizeof(game), 1, file);
        fclose(file);
        printf("Game saved successfully to '%s'.\n", filepath);
    }
    else 
    {
        fprintf(stderr, "Unable to open file for saving.\n");
    }
    free(filename);
}

void loadGame(game* gamePtr) 
{
    char filename[256];  // Assuming a maximum filename length of 255 characters
    
    // List the available saved game files in the current directory
    printf("List of saved games:\n");
    system("ls *.bin");  // Assumes a Unix-like system; modify for Windows if needed

    printf("Enter the name of the file to load: ");
    scanf("%255s", filename);  // Limit the input to 255 characters

    file = fopen(filename, "rb");
    if (file != NULL) 
    {
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Deserialize the game struct
        char* buffer = (char*)malloc(fileSize);
        fread(buffer, fileSize, 1, file);
        memcpy(gamePtr, buffer, sizeof(game));
        free(buffer);

        fclose(file);
        printf("Game loaded successfully from '%s'.\n", filename);
    } 
    else 
    {
        fprintf(stderr, "Unable to open file for loading.\n");
    }
}

// Display the top players and their scores
void printTopPlayers() 
{
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    // Sort the players based on score
    for(int i = 0; i < numPlayers - 1; i++) 
    {
        for(int j = i + 1; j < numPlayers; j++) 
        {
            if(players[j].score > players[i].score) 
            {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Top %d Players :\n", numPlayers);

    int numPlayersToPrint = (numPlayers < MAX_PLAYERS_TO_PRINT) ? numPlayers : MAX_PLAYERS_TO_PRINT;

    for(int i = 0; i < numPlayersToPrint; i++)
    {
        printf("%d. %s -----> %d\n", i + 1, players[i].name, players[i].score);
    }

    // Free dynamically allocated memory
    free(players);
}

//The loadPlayers function deserializes and loads all players from the binary file. It returns a dynamic array of
//Player structs and updates the numPlayers variable.
//The Winner function uses loadPlayers to get the existing players, updates the information for the winner,
//and then saves the updated players back to the file.
//The printTopPlayers function also uses loadPlayers to get the players and then sorts and prints the top players based on their scores.


#endif