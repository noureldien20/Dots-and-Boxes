#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include "Basic_Var_and_Func.h"
#include "Undo_Redo.h"
#include "INPUT.h"
#include "Save_Load.h"

void convertToLowercase(char *str) 
{
    while (*str) 
    {
        *str = tolower((unsigned char)*str);
        str++;
    }
}

void print_options()
{
    printf("To Make a move [Press M]\n");
    printf("To Undo [Press U]\n");
    printf("To Redo [Press R]\n");
    printf("To Save game [Press S]\n");
    printf("To Exit game [Press E]\n");
    printf("Option : ");

    char* temp;
    char op ;
    temp = take_input(5);
    printf("\n");
    if(temp[1] != '\0')
    {
        printf(red"Invalid input\n"RESET);
        print_options();
        return;
    }else
    {
        op = small(temp[0]);
    }
    
    if(op == 'u')
    {
        undo();
        UndoRedoFlag = 1;
        print_grid();
        display_stats();
        return;
    }
    else if(op == 'r')
    {
        redo();
        UndoRedoFlag = 1;
        print_grid();
        display_stats();
        return;
    }
    else if(op =='s')
    {
        saveGame(&current_game);
        print_grid();
        display_stats();
        UndoRedoFlag = 1 ;
        return;
    }
    else if(op =='e')
    {
        exit(1);
    }
    else if(op =='m')
    {
        input_nodes();
        return;
    }
    else
    {
        printf(red"Invalid input\n"RESET);
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

    char *temp2 ; //player 1
    char *temp3 ; //player 2
    char* temp1;
    char op;
    temp1 = take_input(5);
    printf("\n");

    if(temp1[1] != '\0')
    {
        printf(red"Invalid input\n"RESET);
        print_menu() ;
        return;
    }
    else
    {
        op = small(temp1[0]) ;
    }

    if(op == 'l')
    {
        loadGame(&current_game);
        turn = current_game.turn;
        n = current_game.size;   
        declare_arrays();
        copy_current_game_arrays_to_Ahmed();
        empty_stack();
        temp_time = 60;
        return;
    }
    else if(op == 't')
    {
        printTopPlayers();
        
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
            printf(red"Invalid input\n"RESET);
            print_menu();
            return;
        }
        else
        {
            
            input_size() ;
            current_game.size = n ;
            declare_arrays() ;
            inputGameMode() ;
            
            /*
            printf("Enter player 1 name [MAX %d]: ", MAX_NAME_LENGTH);
            
            temp2 = take_input(MAX_NAME_LENGTH + 1) ;
            for(int i = 0 ; i < MAX_NAME_LENGTH ; i++)
            {
                if(temp2[i] == '\0') // valid input
                else call for the funcion again
            }
            strcpy(current_game.player_1.name , temp2) ;
            convertToLowercase(current_game.player_1.name);
            */
            getPlayerName(&current_game.player_1, 1);
            
            if(current_game.mode == 2)
            {
                /*
                printf("Enter player 2 name [MAX %d]: ", MAX_NAME_LENGTH);
                
                temp3 = take_input(MAX_NAME_LENGTH+1) ;
                strcpy(current_game.player_2.name , temp3) ;
                convertToLowercase(current_game.player_2.name);
                */
                getPlayerName(&current_game.player_2, 2);
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