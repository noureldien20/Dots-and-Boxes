#include <stdio.h>

#define MAX_SIZE_OF_STACK 30

#define MAX_PLAYERS_TO_PRINT 10

#define MAX_NAME_LENGHT 20

#define MAX_SIZE_OF_ARRAY 10

typedef struct {
   char name[MAX_NAME_LENGHT];
   int score;
   int number_of_moves;
} player;

typedef struct {
   short int n;
   char array_of_row_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   char array_of_column_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   char array_of_boxes[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   double elapsed_time;
   char turn;
   int number_of_remaining_boxes;
   player player_1;
   player player_2;
   short int previous_sum;

} game;

typedef struct {
   game array[MAX_SIZE_OF_STACK];
   int top;
} Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;

int number_of_filled_boxes() 
{
    // int n, char array[n][n] of boxes
    int sum = 0;

    for (int i = 0; i < current_game.n; ++i) 
    {
        for (int j = 0; j < current_game.n; ++j) 
        {
            sum += current_game.array_of_boxes[i][j] - '0';
        }
    }

    return sum;
}

void switch_turn()
{
    if(number_of_filled_boxes() == current_game.previous_sum)
    {
        //empty(&undo_stack);
        //empty(&redo_stack);
        current_game.turn = (current_game.turn == '1') ? '2' : '1'; /*1 and 2 or a and b*/ //modify the condition
    }
}


int main()
{
    game current_game;
    current_game.turn = '1';
    current_game.n = 3; // Adjust the size accordingly

    // Initialize array_of_boxes with some values for testing
    for (int i = 0; i < current_game.n; ++i) {
        for (int j = 0; j < current_game.n; ++j) {
            current_game.array_of_boxes[i][j] = '1';
        }
    }

    current_game.previous_sum = 9;
    switch_turn();
    printf("NEW: %c", current_game.turn);
}