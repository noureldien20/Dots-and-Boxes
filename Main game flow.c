#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

#include "Basic_Var_and_Func.h"
#include "Save_Load.h"
#include "Menu_Options.h"
#include "Undo_Redo.h"
#include "INPUT.h"
#include "CHECKING.h"
#include "Display.h"

/**player 1 ---> cyan , name1
player 2 ---> green , name2
dots ---> white

line constant --> 7 underscores _
space ---> '\t' --> 7 spaces

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k
**/

/********************************** بسم الله الرحمن الرحيم  **************************************/

int main(){
    printf("Welcome to Dots & Boxes game\n");

    while(1)
    {
        print_menu();

        //pthread_t time_thread ;
        //pthread_create(&time_thread, NULL, time_passed, NULL) ;

        print_grid();
        display_stats();

        while(number_of_filled_boxes() != n*n)
        {   
            temp_time = current_game.elapsed_time + 60;
            //previous_state = current_game;
            current_game.previous_sum = number_of_filled_boxes();
            
            if(current_game.mode == 2) // 2 players
            {
                input_nodes();
            }
            else //play vs computer
            {
                if(turn == '1')
                {
                    input_nodes();
                }
                else //computer turn
                {
                    AI_input();
                    check_edges();
                }
            }
            
            if(UndoRedoFlag != 1)
            {
                print_grid();
                switch_turn();
                display_stats();
            }
        }

        player winnerName = (current_game.player_1.score > current_game.player_2.score)
        ? current_game.player_1
        : current_game.player_2;
        Winner(&winnerName);
        printTopPlayers();
    }
}
