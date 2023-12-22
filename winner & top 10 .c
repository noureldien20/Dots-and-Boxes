#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_PLAYERS_TO_PRINT 10
#define MAX_SIZE_OF_ARRAY 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
} player;

typedef struct {
    unsigned short int size;
    char array_of_row_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_column_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_boxes[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    double elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;
    short int mode; // 1 --> computer
} game;

// Serialize and save the player to a binary file
void savePlayer(const player* player) {
    FILE* file = fopen("player_data.bin", "ab");  // "ab" for append in binary mode

    if (file == NULL) {
        printf("Error opening or creating the file.\n");
        return;
    }

    fwrite(player, sizeof(player), 1, file);

    fclose(file);
}

// Deserialize and load players from a binary file
player* loadPlayers(int* numPlayers) {
    FILE* file = fopen("player_data.bin", "rb");

    if (file == NULL) {
        printf("Error opening the file.\n");
        exit(1);
    }

    player* players = NULL;
    *numPlayers = 0;

    player tempPlayer;

    while (fread(&tempPlayer, sizeof(player), 1, file) == 1) {
        players = realloc(players, (*numPlayers + 1) * sizeof(player));

        if (players == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        players[(*numPlayers)++] = tempPlayer;
    }

    fclose(file);

    return players;
}

// Serialize and save the winner to the file
void Winner(player* winner) {
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    int found = 0;

    // Search for the player in the array
    for (int i = 0; i < numPlayers; i++) {
        if (strcmp(players[i].name, winner->name) == 0) {
            found = 1;

            if (winner->score > players[i].score) {
                players[i].score = winner->score;
            }
            break;
        }
    }

    if (!found) {
        // Add the winner to the array
        players = realloc(players, (numPlayers + 1) * sizeof(player));

        if (players == NULL) {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        players[numPlayers++] = *winner;
    }

    // Save the updated players to the file
    FILE* file = fopen("player_data.bin", "wb");
    if (file != NULL) {
        fwrite(players, sizeof(player), numPlayers, file);
        fclose(file);
    } else {
        printf("Error opening the file for saving.\n");
    }

    // Free dynamically allocated memory
    free(players);
}

// Display the top players and their scores
void printTopPlayers() {
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    // Sort the players based on score
    for (int i = 0; i < numPlayers - 1; i++) {
        for (int j = i + 1; j < numPlayers; j++) {
            if (players[j].score > players[i].score) {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Top %d Players:\n", numPlayers);

    int numPlayersToPrint = (numPlayers < MAX_PLAYERS_TO_PRINT) ? numPlayers : MAX_PLAYERS_TO_PRINT;

    for (int i = 0; i < numPlayersToPrint; i++) {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }

    // Free dynamically allocated memory
    free(players);
}
/*The savePlayer function serializes and saves a single player to the binary file in append mode ("ab").

The loadPlayers function deserializes and loads all players from the binary file. It returns a dynamic array of Player structs and updates the numPlayers variable.

The Winner function uses loadPlayers to get the existing players, updates the information for the winner, and then saves the updated players back to the file.

The printTopPlayers function also uses loadPlayers to get the players and then sorts and prints the top players based on their scores.*/

int main() {
    // Example usage
    player winner = {"Player1", 100};  // Set some values for demonstration

    // Save the winner to the file
    Winner(&winner);

    // Display the top players
    printTopPlayers();

    player winner1 = {"Player2", 110};  // Set some values for demonstration

    // Save the winner to the file
    Winner(&winner1);

    // Display the top players
    printTopPlayers();

    player winner2 = {"Player3", 50};  // Set some values for demonstration

    // Save the winner to the file
    Winner(&winner2);

    // Display the top players
    printTopPlayers();

    player winner3 = {"Player1", 120};  // Set some values for demonstration

    // Save the winner to the file
    Winner(&winner3);

    // Display the top players
    printTopPlayers();

    return 0;
}
