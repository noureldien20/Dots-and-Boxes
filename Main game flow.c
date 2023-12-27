#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include <pthread.h>

#include "Basic_Var_and_Func.h"
#include "Save_Load.h"
#include "Menu_Options.h"
#include "Undo_Redo.h"
#include "INPUT.h"
#include "CHECKING.h"
#include "Display.h"

/********************************** بسم الله الرحمن الرحيم  *************************************/

int main()
{
    printf("Welcome to Dots & Boxes game\n");

    while(1)
    {
        print_menu();

        //pthread_t time_thread ;
        //pthread_create(&time_thread, NULL, time_passed, NULL) ;

        print_grid();

        while(number_of_filled_boxes() != n*n)
        {
            current_game.previous_sum = number_of_filled_boxes();
            clearInputBuffer();
            input_nodes();
            check_edges();
            print_grid();
            switch_turn();
            display_stats();
            Copy_Arrays_To_Struct(&current_game);
            push(&undo_stack, current_game);
        }

        player winnerName = (current_game.player_1.score > current_game.player_2.score)
        ? current_game.player_1
        : current_game.player_2;
        Winner(&winnerName);
        printTopPlayers();
    }
}
