#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE_OF_STACK 30

typedef struct 
{
    double elapsed_time;
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
    stack->top = 0;

    game zero;
    zero.elapsed_time = 0;
    zero.turn = 'A';

    stack->array[0] = zero;
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

game undo_stack(Stack *undo_stack,Stack *redo_stack, game before_current)
{
    if (before_current.turn == peek(undo_stack).turn)
    {
        push(&redo_stack, pop(&undo_stack));
        
        printf("Undo successful.\n");
    } 
    else 
    {
        printf("u can't undo_stack anymore.\n");
    }

    return peek(&undo_stack);
}

void redo_stack(Stack *undo_stack,Stack *redo_stack, game after_current)
{
    if (after_current.turn == peek(redo_stack).turn)
    {
        push(&undo_stack, pop(&redo_stack));
 
        printf("Redo successful.\n");
    } 
    else 
    {
        printf("u can't redo_stack anymore\n");
    }

    return peek(&undo_stack);
}

int main()
{
    initialize_stacks();

    game current;

    while (1)
    {
        printf("enter time: ");
        scanf("%lf", &current.elapsed_time);

        printf("enter turn: ");
        scanf("%c", &current.turn);

        char option;
        printf("enter option num: ");
        scanf("%c", &option);

        switch (option)
        {
        case 'u':
            undo_stack(&undo_stack, &redo_stack, current);
            break;
        case 'r':
            redo_stack(&undo_stack, &redo_stack, current);
            break;
        case 's' : 
            break;
        default:
            break;
        }
    }
    


}