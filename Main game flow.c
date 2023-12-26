#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Basic Var and Func.h"
#include "INPUT.h"
#include "CHECKING.h"
#include "Display.h"
#include <pthread.h>
#include <time.h>
//#include "temperory game"

/******************************** بسم الله الرحمن الرحيم  *********************************/

int main(){
printf("Welcome to Dots & Boxes game\n");

while(1 /* lw m3ml4 quit */){ // bta3t el brnamg kolo

print_menu();

pthread_t time_thread ;
pthread_create(&time_thread, NULL, time_passed, NULL) ;

print_grid();

while(1 /* number of filled boxes = n*n */){

    //current_game.previous_sum = number_of_filled_boxes();
    input_nodes();
    check_edges();
    print_grid();
    printf("%d",t);
    //switch_turn();
    //display_stats();
}
//free game matrices & variables
free(row_edges) ;
free(col_edges) ;
free(boxes) ;
free(dfs);
t = 0 ;

}

}
