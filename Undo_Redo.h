#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "Basic_Var_and_Func.h"
#include "Menu_Options.h"

void push()
{
    copy_current_game_arrays_from_Ahmed();
    Game_stack.array[++Game_stack.pointer_to_index] = current_game;
}

void undo()
{
    if (Game_stack.pointer_to_index > 0)
    {
        Game_stack.pointer_to_index--;
        current_game = Game_stack.array[Game_stack.pointer_to_index];
        copy_current_game_arrays_to_Ahmed();

        printf("\n\nUndo successful.\n\n");
    }
    else 
    {
        printf("\n\nu can't undo anymore.\n\n");
    }
}

void redo()
{
    if (Game_stack.array[Game_stack.pointer_to_index + 1].index_flag > 0)
    {
        Game_stack.pointer_to_index++;

        current_game = Game_stack.array[Game_stack.pointer_to_index];
        copy_current_game_arrays_to_Ahmed();

        //copy_game_arrays_to_Ahmed();

        printf("\n\nRedo successful.\n\n");
    } 
    else 
    {
        printf("\n\nu can't redo anymore\n\n");
    }
}

void empty_redo_stack()
{
    for(int i = Game_stack.pointer_to_index + 1 ; i < MAX_SIZE_OF_STACK ; i++)
    {
        if(Game_stack.array[i].index_flag == 0)
        {
            break;
        }
        else
        {
            Game_stack.array[i].index_flag = 0;
        }
    }
}

void empty_stack()
{
    for(int i = 0 ; i < MAX_SIZE_OF_STACK ; i++)
    {
        if(Game_stack.array[i].index_flag == 0)
        {
            break;
        }
        else
        {
            Game_stack.array[i].index_flag = 0;
        }
    }

    Game_stack.pointer_to_index = -1;
}

#endif