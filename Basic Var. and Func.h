#ifndef BASIC_VAR._AND_FUNC_H
#define BASIC_VAR._AND_FUNC_H

#include <stdio.h>
#include <stdlib.h>

/******************************** بسم الله الرحمن الرحيم  ***********************************/

#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define blue "\e[0;34m"
#define cyan "\e[0;36m"
#define white "\e[0;37m"
#define back_cyan "\e[46m"
#define back_green "\e[42m"
#define back_white "\e[47m"

#define Ctrl_Z '\x1A'
#define Ctrl_R '\x12'
#define Ctrl_S '\x13'

/** Names of variables
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k **/

unsigned short int n ;
char **row_edges ;  //2D array of the edges of rows  ( of size [n+1][n])
char **col_edges ;  //2D array of the edges of columns ( of size[n][n+1])
char **boxes ;  //2D array of access of boxes and who close every box ( of size[n][n] )
char **dfs ;
char turn ;
unsigned long t ;

// mode indicator
short int mode ;  // 1 --> computer

void zero_2D_array(short int row,short int col,char **arr){
   for (int i=0 ; i<row ; i++){
      for (int j=0 ; j<col ; j++){
         arr[i][j] = '0' ; }
   }
}

void print_array_2D(short int row,short int col,char **arr){
   for (short int i=0 ; i<row ; i++){
      for (short int j=0 ; j<col ; j++){
      printf("%c ",arr[i][j]);
      }
      printf("\n");
   }
}

char **create_array(short int row,short int col){
   char **arr = (char**)calloc((row),sizeof(char*)) ;

   for(short int i=0 ; i<row ; i++){
      arr[i] = (char*)calloc(col, sizeof(char));
   }
   return arr ;
}

void declare_arrays(){
   row_edges = create_array(n+1,n) ;
   col_edges = create_array(n,n+1) ;
   boxes = create_array(n,n) ;
   dfs = create_array(n,n) ;
}

char small(char c){
   if (c>=65 && c<=90){ return c+32 ; }
   else{return c ;}
}

char big(char c){
   if (c>=97 && c<=122){ return c-32 ; }
   else{return c ;}
}

void time_passed(){

   /*while(win != n*n){
      sleep(1) ;
      game.time++ ;
   }
 */
}











#define MAX_SIZE_OF_STACK 30

#define MAX_PLAYERS_TO_PRINT 10

#define MAX_NAME_LENGHT 20

#define MAX_SIZE_OF_ARRAY 10

typedef struct {
   char name[MAX_NAME_LENGHT];
   int score;
   int number_of_moves;
}player;

typedef struct{
    short int n;
    char array_of_row_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_column_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_boxes[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    double elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;

}game;

typedef struct {
    game array[MAX_SIZE_OF_STACK];
    int top;
}Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;
