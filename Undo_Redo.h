#ifndef UNDO_REDO_H
#define UNDO_REDO_H

#include "Basic_Var_and_Func.h"
#include "Menu_Options.h"

/*void push()
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
}*/



void push(){
    Game_stack.pointer_to_index++;
    printf("\npointer index (push)before = %d\n",Game_stack.pointer_to_index);
    copy_current_game_arrays_from_Ahmed();
    //Game_stack.array[Game_stack.pointer_to_index] = current_game;
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
    printf("i entered the push  %c\n", current_game.array_of_column_edges[0][1]);
    printf("i entered the push function %c\n", Game_stack.array[Game_stack.pointer_to_index].array_of_column_edges[0][1]);
}

void undo(){

    printf("%d",Game_stack.pointer_to_index) ;
    if (Game_stack.pointer_to_index > 0)
    {
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
        //current_game = Game_stack.array[Game_stack.pointer_to_index];
        copy_current_game_arrays_to_Ahmed();
        printf("\n\nUndo is done successfully\n\n");
        
    }else{
        printf("\n\nCannot undo anymore\n\n");
    }
}

void redo(){

    if (Game_stack.array[Game_stack.pointer_to_index + 1].index_flag == 1)
    {
        Game_stack.pointer_to_index++;
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
        //current_game = Game_stack.array[Game_stack.pointer_to_index];
        copy_current_game_arrays_to_Ahmed();

        printf("\n\nRedo successful.\n\n");
    }else{
        printf("\n\nu can't redo anymore\n\n");
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

void delete_stack_values(){
    for(int k=0 ; k <= Game_stack.pointer_to_index ; k++){ // for every structure in stack

        for(int i=0 ; i<n ; i++){
            for(int j=0 ; j<n ; j++){

                boxes[i][j] = '\0';
                row_edges[i][j] = '\0' ;
                col_edges[i][j] = '\0' ;

            }
            row_edges[n][i] = '\0' ;
            col_edges[i][n] = '\0' ;
        }

    }
}



#endif
