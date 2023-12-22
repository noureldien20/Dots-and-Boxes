#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_SIZE_OF_ARRAY 10

typedef struct {
    char name[MAX_NAME_LENGTH];
    int score;
    int number_of_moves;
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

// Global FILE pointer
FILE* file;

// Function to serialize and save the game to a binary file
int saveGame(const game* gamePtr) {
    file = fopen("saved_game.bin", "wb");
    if (file != NULL) {
        // Serialize the game struct
        fwrite(gamePtr, sizeof(game), 1, file);
        fclose(file);
        printf("Game saved successfully.\n");
        return 1;
    } else {
        fprintf(stderr, "Unable to open file for saving.\n");
        return 0;
    }
}

// Function to deserialize and load the game from a binary file
int loadGame(game* gamePtr) {
    file = fopen("saved_game.bin", "rb");
    if (file != NULL) {
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
        return 1;
    } else {
        fprintf(stderr, "Unable to open file for loading.\n");
        return 0;
    }
}

int main() {
    // Example usage
    game current_game;
    current_game.size = 3;  // Set some values for demonstration

    // Save the game
    saveGame(&current_game);

    // Load the game into a new struct
    game loaded_game;
    loadGame(&loaded_game);

    // Verify that the loaded game is the same as the current game
    printf("Loaded Game Size: %hu\n", loaded_game.size);

    return 0;
}