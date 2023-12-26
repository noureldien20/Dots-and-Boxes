#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "Basic Var and Func.h"

#define MAX_SIZE_OF_STACK 15

typedef struct 
{
    game array[MAX_SIZE_OF_STACK];
    int top;
} Stack;

Stack undo_stack;
Stack redo_stack;


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




#endif