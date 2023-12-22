#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Basic Var. and Func.h"
#include "INPUT.h"
#include "Display.h"
#include <pthread.h>

/******************************** بسم الله الرحمن الرحيم  *********************************/
Create_thread() ;

int main(){
printf("Welcome to Dots & Boxes game\n") ;
while(1){

print_menu() ;

printf("Enter [0] to play Vs human\n") ;
printf("Enter [1] to play Vs computer\n") ;
//function to input mode 
printf("Enter name of player 1 : ") ;
if (!mode){
    printf("Enter name of player 2 : ") ;
}

print_grid() ;

while(number_of_filled_boxes() != n*n){
    input_edge() ;
    check_edges() ;
    print_grid() ;
    input_nodes() ;
    display_stats();
    /**nour hyn2l el wr2a


//print options
printf("test") ;
*/
}
}
}
