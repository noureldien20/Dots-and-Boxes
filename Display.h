#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include "Basic Var. and Func.h"

#define line "_______"

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
      printf(back_cyan"       ") ;
   }else if(boxes[c-1][i]=='2'){
      printf(back_green"       ") ;
   }else{
      printf("       ") ;
   }
}

void print_horizontal(short int r,short int n,char row_edges[][n]){
   int i ;   ///r is not index , if r=2 ---> row that has index 1
   for(i=0 ; i<n ; i++){
      printf(white".") ;

      if (row_edges[r-1][i] == 1){
         printf(cyan"%s",line) ;
      }else if(row_edges[r-1][i] == 2){
         printf(green"%s",line) ;
      }else{
         printf("\t") ;
      }
   }
   printf(white".\n") ;
}

void print_vertical(short int c,short int n,char col_edges[][n+1]){
   int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<n ; i++){

         if(col_edges[c-1][i]=='1' || boxes[c-1][i]=='1'){
            printf(cyan"|") ;
         }else if(col_edges[c-1][i]=='2' || boxes[c-1][i]=='2'){
            printf(green"|") ;
         }else{
            printf(" ") ;
         }
         print_boxes_color(c,i) ;
      }

   if (col_edges[c-1][i]=='1'){
      printf(cyan"|\n");
   }else if(col_edges[c-1][i]=='2'){
      printf(green"|\n") ;
   }else{
      printf(" \n") ;
      }
   }
}

void print_grid(short int n){
   int j ;
   for(j=1 ; j<=n ; j++){
      print_horizontal(j,n,row_edges) ;
      print_vertical(j,n,col_edges) ;
   }
   print_horizontal(j,n,row_edges) ;
}

void print_menu(){
   
   printf("To Start game [Press S]\n");
   printf("To load previous game [Press L]\n");
   printf("To display Top 10 players [Press T]\n");
   printf("To Exit game [Press E]\n");

   char o ;
   scanf("%c",&o) ;
   if(lower(o) == 'l'){
      // function to load from file
   }else if(lower(o) == 't'){
      //function to print top 10
      print_menu() ;
   }else if(lower(o) =='e'){
      exit(1) ;
   }else{

      if(lower(o)!='s'){
         print_menu() ;
      }else{
         input_size() ;
         declare_arrays(n) ;
      }

   }
   
}

#endif