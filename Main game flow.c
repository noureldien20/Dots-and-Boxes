#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Basic Var. and Func.h"
#include "INPUT.h"
#include "CHECKING.h"
#include "Display.h"
#include <pthread.h>

/******************************** بسم الله الرحمن الرحيم  *********************************/

int main(){

pthread_t time_thread ;
pthread_create(&time_thread, NULL, time_passed, NULL) ;

printf("Welcome to Dots & Boxes game\n") ;
while(1){

print_menu() ;

printf("Enter [0] to play Vs human\n") ;
printf("Enter [1] to play Vs computer\n") ;
//function to input mode
printf("Enter name of player 1 : ") ;

/*if (!mode){
    printf("Enter name of player 2 : ") ;
}*/

print_grid() ;

while(number_of_filled_boxes() != n*n){

    input_nodes() ;

    if(check_edges()){
        //Make DFS
        //do not switch turn
    }else{
        //switch turn
    }
    print_grid() ;

    print_status(); // print(turn , moves , scores , number of remaining boxes , time passed)

    //print options
}


}
}
