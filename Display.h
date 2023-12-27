#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>

#include "Basic_Var_and_Func.h"
             
#define line "-------"

/******************************** بسم الله الرحمن الرحيم  ************************************/

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

void print_boxes_color(short int c,short int i){
   if (boxes[c-1][i]=='1'){
      printf(back_cyan"       "RESET) ;
   }else if(boxes[c-1][i]=='2'){
      printf(back_green"       "RESET) ;
   }else{
      printf("       ") ;
   }
}

void print_horizontal(short int r){
   short int i ;   ///r is not index , if r=2 ---> row that has index 1
   for(i=0 ; i<n ; i++){
      printf(white"+"RESET) ;

      if (row_edges[r-1][i] == '1'){
         printf(cyan"%s"RESET,line) ;
      }else if(row_edges[r-1][i] == '2'){
         printf(green"%s"RESET,line) ;
      }else{
         printf("       ") ;
      }
   }
   printf(white"+\n"RESET) ;
}

void print_vertical(short int c){
   short int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<n ; i++){

         if(col_edges[c-1][i]=='1' || boxes[c-1][i]=='1'){
            printf(cyan"|"RESET) ;
         }else if(col_edges[c-1][i]=='2' || boxes[c-1][i]=='2'){
            printf(green"|"RESET) ;
         }else{
            printf(" ") ;
         }
         print_boxes_color(c,i) ;
      }

   if (col_edges[c-1][i]=='1'){
      printf(cyan"|\n"RESET);
   }else if(col_edges[c-1][i]=='2'){
      printf(green"|\n"RESET) ;
   }else{
      printf(" \n") ;
      }
   }
}

void print_grid(){
   printf("\n");
   short int j ;
   for(j=1 ; j<=n ; j++){
      print_horizontal(j) ;
      print_vertical(j) ;
   }
   print_horizontal(j) ;
   printf("\n");
}

void display_stats()
{
   printf("\nNext turn: %s\n", turn == '1' ? current_game.player_1.name : current_game.player_2.name);
   printf("Player:\t%s\t%s\n", current_game.player_1.name, current_game.player_2.name);
   printf("Score:\t%d\t%d\t\n", current_game.player_1.score, current_game.player_2.score);
   printf("Moves:\t%d\t%d\t\n", current_game.player_1.number_of_moves, current_game.player_2.number_of_moves);
   printf("Remaining Boxes: %d\n", current_game.number_of_remaining_boxes);
   printf("Time: %d:%d\n", current_game.elapsed_time / 60, current_game.elapsed_time % 60 );
}

#endif