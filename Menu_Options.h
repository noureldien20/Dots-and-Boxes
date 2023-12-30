#ifndef MENU_OPTIONS_H
#define MENU_OPTIONS_H

#include "Basic_Var_and_Func.h"
#include "Undo_Redo.h"
#include "INPUT.h"
#include "Save_Load.h"

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
            scanf("%40s", current_game.player_1.name);
            
            if(current_game.mode == 0)
            {
                printf("Enter player 2 name: ");
                clearInputBuffer();
                scanf("%40s", current_game.player_2.name);
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