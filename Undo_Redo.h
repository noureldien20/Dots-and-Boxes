#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "Basic_Var_and_Func.h"
#include "Menu_Options.h"

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

        *current = peek(undo_stack);
        copy_struct_to_arrays(&current_game);
        turn = current_game.turn;
        print_grid();
        display_stats();
    } 
    else 
    {
        printf("u can't undo anymore.\n");
    }
}

void redo(Stack *undo_stack,Stack *redo_stack, game *current)
{
    if (current->turn == peek(redo_stack).turn && undo_stack->top != -1)
    {
        push(undo_stack, pop(redo_stack));
 
        printf("Redo successful.\n");

        *current = peek(undo_stack);
        copy_struct_to_arrays(&current_game);
        turn = current_game.turn;
        print_grid();
        display_stats();
    } 
    else 
    {
        printf("u can't redo anymore\n");
    }
}

#endif