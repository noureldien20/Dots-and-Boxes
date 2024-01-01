#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "Basic_Var_and_Func.h"
#include "Menu_Options.h"


void push(){
    Game_stack.pointer_to_index++;

    //Copy “current_game“ data to the to the top of the stack
    
    copy_current_game_arrays_from_Ahmed();
    Game_stack.array[Game_stack.pointer_to_index].index_flag = current_game.index_flag;
    Game_stack.array[Game_stack.pointer_to_index].size = current_game.size;
    Game_stack.array[Game_stack.pointer_to_index].turn = current_game.turn;
    Game_stack.array[Game_stack.pointer_to_index].number_of_remaining_boxes = current_game.number_of_remaining_boxes;
    Game_stack.array[Game_stack.pointer_to_index].previous_sum = current_game.previous_sum;
    Game_stack.array[Game_stack.pointer_to_index].mode = current_game.mode;

    for (int i = 0; i < n ; i++)
    {
        for (int j = 0; j < n ; j++)
        {

            Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[i][j] = current_game.array_of_row_edges[i][j] ;
            Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][j] = current_game.array_of_column_edges[i][j] ;
            Game_stack.array[Game_stack.pointer_to_index].array_of_boxes[i][j] = current_game.array_of_boxes[i][j] ;
        }

        Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[n][i] = current_game.array_of_row_edges[n][i] ;
        Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][n] = current_game.array_of_column_edges[i][n] ;
    }

}

void undo(){

    if (Game_stack.pointer_to_index > 0) //Check if the “pointer_to_index” is bigger than zero (stack not empty)
    {
        //Copy the data from the game at top of stack to “current_game”
        Game_stack.pointer_to_index--;
        current_game.index_flag = Game_stack.array[Game_stack.pointer_to_index].index_flag;
        current_game.size = Game_stack.array[Game_stack.pointer_to_index].size;
        current_game.turn = Game_stack.array[Game_stack.pointer_to_index].turn;
        current_game.number_of_remaining_boxes = Game_stack.array[Game_stack.pointer_to_index].number_of_remaining_boxes;
        current_game.previous_sum = Game_stack.array[Game_stack.pointer_to_index].previous_sum;
        current_game.mode = Game_stack.array[Game_stack.pointer_to_index].mode;

        for (int i = 0; i < n ; i++)
        {
            for (int j = 0; j < n ; j++)
            {

                current_game.array_of_row_edges[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[i][j] ;
                current_game.array_of_column_edges[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][j] ;
                current_game.array_of_boxes[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_boxes[i][j] ;
            }

            current_game.array_of_row_edges[n][i] = Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[n][i] ;
            current_game.array_of_column_edges[i][n] = Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][n] ;
        }

        copy_current_game_arrays_to_Ahmed();
        printf(green"\nUndo is done successfully\n"RESET);
        
    }else{
        printf(red"\nCannot undo anymore\n"RESET);
    }
}

void redo(){

    if (Game_stack.array[Game_stack.pointer_to_index + 1].index_flag == 1)
    {
        //Check if the “index_flag” of the game after the top of stack = 1 (a game exists and can be copies)

        Game_stack.pointer_to_index++;
        
        //Copy the data from the game after the top of stack to “current_game” (currently at the top of the stack)
        current_game.index_flag = Game_stack.array[Game_stack.pointer_to_index].index_flag;
        current_game.size = Game_stack.array[Game_stack.pointer_to_index].size;
        current_game.turn = Game_stack.array[Game_stack.pointer_to_index].turn;
        current_game.number_of_remaining_boxes = Game_stack.array[Game_stack.pointer_to_index].number_of_remaining_boxes;
        current_game.previous_sum = Game_stack.array[Game_stack.pointer_to_index].previous_sum;
        current_game.mode = Game_stack.array[Game_stack.pointer_to_index].mode;

        for (int i = 0; i < n ; i++)
        {
            for (int j = 0; j < n ; j++)
            {

                current_game.array_of_row_edges[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[i][j] ;
                current_game.array_of_column_edges[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][j] ;
                current_game.array_of_boxes[i][j] = Game_stack.array[Game_stack.pointer_to_index].array_of_boxes[i][j] ;
            }

            current_game.array_of_row_edges[n][i] = Game_stack.array[Game_stack.pointer_to_index].array_of_row_edges[n][i] ;
            current_game.array_of_column_edges[i][n] = Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[i][n] ;
        }

        copy_current_game_arrays_to_Ahmed();

        printf(green"\nRedo is done successfully.\n"RESET);
    }else{
        printf(red"\nCannot redo anymore\n"RESET);
    }
}

void empty_redo_stack(){

    for(int i = Game_stack.pointer_to_index + 1 ; i < MAX_SIZE_OF_STACK ; i++){
        if(Game_stack.array[i].index_flag == 0){
            break;
        }else{
            Game_stack.array[i].index_flag = 0;
        }
    }
}
/*
It loops from the game after the top of the stack and stops when it encounters “index_flag” equal to zero
The loop checks if the “index_flag” is equal to 1 if yes if changes it to zero
*/

void empty_stack()
{
    for(int i = 0 ; i < MAX_SIZE_OF_STACK ; i++)
    {
        if(Game_stack.array[i].index_flag == 0){
            break;
        }else{
            Game_stack.array[i].index_flag = 0 ;
        }
    }

    Game_stack.pointer_to_index = -1 ;
}
/*
It loops from the beginning of the stack until it encounters a “index_flag” equal to zero
The loop checks if the “index_flag” is equal to 1 if yes if changes it to zero
*/

#endif
