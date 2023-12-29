#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include "Basic_Var_and_Func.h"
#include "Undo_Redo.h"
#include "INPUT.h"
#include "Save_Load.h"



void copy_struct_to_arrays(game* gamePtr) 
{
    // Copy array_of_row_edges
    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            row_edges[i][j] = gamePtr->array_of_row_edges[i][j];
        }
    }

    // Copy array_of_column_edges
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            col_edges[i][j] = gamePtr->array_of_column_edges[i][j];
        }
    }

    // Copy array_of_boxes
    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            boxes[i][j] = gamePtr->array_of_boxes[i][j];
        }
    }
}

void reset_variables_to_zeros()
{
    turn = '1';
    current_game.player_1.number_of_moves = 0;
    current_game.player_2.number_of_moves = 0;
    current_game.player_1.score = 0;
    current_game.player_2.score = 0;
    empty_both_stacks();
    current_game.elapsed_time = 0;
}

void print_options()
{
    printf("To Make a move [Press M]\n");
    printf("To Undo [Press U]\n");
    printf("To Redo [Press R]\n");
    printf("To Save game [Press S]\n");
    printf("To Exit game [Press E]\n");
    printf("Option : ");

    char temp[5] ;
    char op ;
    scanf("%1s",temp) ;

    if(temp[1]!='\0')
    {
        printf("Invalid input\n");
        clearInputBuffer();
        print_options();
        return;
    }else
    {
        op = small(temp[0]);
    }
    
    if(op == 'u')
    {
        undo(&undo_stack, &redo_stack, &current_game);
        clearInputBuffer();
        input_nodes();
        return;
    }
    else if(op == 'r')
    {
        redo(&undo_stack, &redo_stack, &current_game);
        clearInputBuffer();
        input_nodes();
        return;
    }
    else if(op =='s')
    {
        saveGame(&current_game);
        return;
    }
    else if(op =='e')
    {
        exit(1);
    }
    else if(op =='m')
    {
        clearInputBuffer();
        input_nodes();
        return;
    }
    else
    {
        printf("Invalid input\n");
        clearInputBuffer();
        print_options();
        return;
    }
}

void print_menu()
{
    printf("\nTo Start game [Press S]\n");
    printf("To load previous game [Press L]\n");
    printf("To display Top 10 players [Press T]\n");
    printf("To Exit game [Press E]\n");
    printf("Option: ");

    char temp[5] ;
    char op ;
    scanf("%1s",temp);

    if(temp[1]!='\0')
    {
        printf("Invalid input\n");
        clearInputBuffer();
        print_menu() ;
        return;
    }
    else
    {
        op = small(temp[0]) ;
    }

    if(op == 'l')
    {
        loadGame(&current_game);
        turn = current_game.turn;
        n = current_game.size;
        declare_arrays();
        copy_struct_to_arrays(&current_game);
        return;
    }
    else if(op == 't')
    {
        printTopPlayers();
        clearInputBuffer();
        print_menu();
        return;
    }
    else if(op == 'e')
    {
        exit(1);
    }
    else
    {
        if(op !='s')
        {
            clearInputBuffer();
            print_menu();
            return;
        }
        else
        {
            clearInputBuffer();
            input_size();
            current_game.size = n;

            declare_arrays();

            clearInputBuffer();

            inputGameMode();
            
            printf("Enter player 1 name: ");
            clearInputBuffer();
            scanf("%40s", &current_game.player_1.name);
            
            if(current_game.mode == 0)
            {
                printf("Enter player 2 name: ");
                clearInputBuffer();
                scanf("%40s", &current_game.player_2.name);
            }
            else
            {
                strcpy(current_game.player_2.name , "computer");
            }

            reset_variables_to_zeros();
        }
    }
}

#endif