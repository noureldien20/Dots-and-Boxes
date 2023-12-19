#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_OF_STACK 30

typedef struct 
{
    double number_of_moves;
    char turn;
} game;

// Structure to represent the stack
typedef struct 
{
    game array[MAX_SIZE_OF_STACK];
    int top; 
} Stack;

Stack undo_stack;
Stack redo_stack;

void initialize_undo_stack(Stack* stack) 
{
    stack->top = -1;
}

void initialize_redo_stack(Stack* stack) 
{
    stack->top = -1;
}

void initialize_stacks(void)
{
    initialize_undo_stack(&undo_stack);
    initialize_redo_stack(&redo_stack);

    printf("stacks initialized successfully\n");
}

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

void empty(Stack *stack)
{
    stack->top = -1;
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
        printf("u can't undo_stack anymore.\n");
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
        printf("u can't redo_stack anymore\n");
    }

    *current = peek(undo_stack);
}

int main()
{
    initialize_stacks();

    game current;
    current.number_of_moves = 0;
    current.turn = 'A';

    push(&undo_stack, current);

    printf("Current game: number of moves: %.2lf, Turn: %c\n", current.number_of_moves, current.turn);

    while (1)
    {
        printf("enter number of moves: ");
        scanf("%lf", &current.number_of_moves);

        int option;
        printf("enter option num: ");
        scanf("%d", &option);

        if(option == 1)
        {
            undo(&undo_stack, &redo_stack, &current);
        }
        else if(option == 2)
        {
            redo(&undo_stack, &redo_stack, &current);
        }
        else
        {
            push(&undo_stack, current);
        }

        printf("After operation\nCurrent game: number of moves: %.2lf, Turn: %c\n", current.number_of_moves, current.turn);
    }
}