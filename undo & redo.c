#include <stdio.h>
#include <stdlib.h>
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
    int previous_sum;

} game;

typedef struct {
    game array[MAX_SIZE_OF_STACK];
    int top;
} Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;

game peek(Stack* stack)
{
    return stack->array[stack->top];
}

game pop(Stack* stack) 
{
    return stack->array[stack->top--];
}

void push(Stack *stack, game game)
{
    stack->array[++stack->top] = game;
}

void empty(Stack *stack) // also used to initialize the stack
{
    stack->top = -1;
}
void empty_both_stacks()
{
    empty(&undo_stack);
    empty(&redo_stack);
}

void undo(Stack *undo_stack,Stack *redo_stack, game *current)
{
    if (current->turn == peek(undo_stack).turn && undo_stack->top != -1)
    {
        push(redo_stack, pop(undo_stack));
        
        printf("Undo successful.\n");
    } 
    else 
    {
        printf("u can't undo anymore.\n");
    }

    *current = peek(undo_stack);
}

void redo(Stack *undo_stack,Stack *redo_stack, game *current)
{
    if (current->turn == peek(redo_stack).turn && undo_stack->top != -1)
    {
        push(undo_stack, pop(redo_stack));
 
        printf("Redo successful.\n");
    } 
    else 
    {
        printf("u can't redo anymore\n");
    }

    *current = peek(undo_stack);
}

int number_of_filled_boxes() 
{
    int count = 0;

    for (int i = 0; i < current_game.n; ++i) 
    {
        for (int j = 0; j < current_game.n; ++j) 
        {
            if (current_game.array_of_boxes[i][j] == '1' || current_game.array_of_boxes[i][j] == '2') 
            {
                count++;
            }
        }
    }

    return count;
}

void switch_turn()
{
    if(number_of_filled_boxes() == current_game.previous_sum)
    {
        printf("entered fn ");
        empty_both_stacks();
        current_game.turn = (current_game.turn == '1') ? '2' : '1'; /*1 and 2 or a and b*/ //modify the condition
    }
    current_game.previous_sum = number_of_filled_boxes();
}
