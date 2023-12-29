#ifndef BASIC_VAR_AND_FUNC_H
#define BASIC_VAR_AND_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <pthread.h>

void empty_both_stacks();

/******************************** بسم الله الرحمن الرحيم  ***********************************/

#define green "\x1b[0;92m"
#define yellow "\x1b[0;93m"
#define cyan "\x1b[96m"
#define white "\x1b[97m"
#define back_cyan "\x1b[106m"
#define back_green "\x1b[102m"
#define back_white "\x1b[107m"
#define RESET "\x1b[0m"

#define Ctrl_Z '\x1A'
#define Ctrl_R '\x12'
#define Ctrl_S '\x13'

/** Names of variables
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k **/

#define MAX_PLAYERS_TO_PRINT 10
#define MAX_NAME_LENGHT 40
#define MAX_GRID_SIZE 10
#define MAX_SIZE_OF_STACK 15

typedef struct 
{
   char name[MAX_NAME_LENGHT + 1];
   int score;
   int number_of_moves;
} player;

typedef struct 
{
    unsigned short int size;
    char array_of_row_edges[MAX_GRID_SIZE + 1][MAX_GRID_SIZE];
    char array_of_column_edges[MAX_GRID_SIZE][MAX_GRID_SIZE + 1];
    char array_of_boxes[MAX_GRID_SIZE][MAX_GRID_SIZE];
    unsigned int elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;
    unsigned short int mode; // 1 --> computer
} game;

typedef struct 
{
    game array[MAX_SIZE_OF_STACK];
    int top;
} Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;

unsigned short int n ;
char **row_edges ;  //2D array of the edges of rows  ( of size [n+1][n])
char **col_edges ;  //2D array of the edges of columns ( of size[n][n+1])
char **boxes ;  //2D array of access of boxes and who close every box ( of size[n][n] )
char **dfs ;
char turn = '1' ;

// n_empty = (n_edges/2) - 2

short int n_edges = 3 ; //number of filled edges in chain
short int n_empty = 1 ; //number of empty edges in chain

short int indexes[3] = {0,0,0} ; 
//third element in indexes array express row or col  [row ---> 0] , [col ---> 1]

short int director = 0 ;  // [director]  up ---> 1 , down ---> -1
// [director]  right ---> 2 , left ---> -2

// mode indicator
short int mode ;  // 1 --> computer

void clearInputBuffer() 
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) 
    {
        // Keep reading characters until newline or end of file
    }
}

void zero_2D_array(short int row,short int col,char **arr){
   for (int i=0 ; i<row ; i++){
      for (int j=0 ; j<col ; j++){
         arr[i][j] = '\0' ; }
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

short int number_of_filled_boxes() 
{
    short int count = 0;

    for (short int i = 0; i < current_game.size; ++i) 
    {
        for (short int j = 0; j < current_game.size; ++j) 
        {
            if (boxes[i][j] != '\0')
            {
                count++;
            }
        }
    }
    return count;
}

void time_passed()
{
   while((number_of_filled_boxes()) != n*n)
   {
      Sleep(1000) ;
      current_game.elapsed_time++; 
   }
}

void switch_turn()
{
    int temp = number_of_filled_boxes();

    if (turn == '1') 
    {
        current_game.player_1.number_of_moves++;
    } 
    else 
    {
        current_game.player_2.number_of_moves++;
    }

    if(temp == current_game.previous_sum)
    {
        empty_both_stacks();
        turn = (turn == '1') ? '2' : '1';
        current_game.turn = turn;
    }
    else
    {
        if (turn == '1') 
        {
            current_game.player_1.score += temp - current_game.previous_sum;
        } 
        else 
        {
            current_game.player_2.score += temp - current_game.previous_sum;
        }
    }
    current_game.number_of_remaining_boxes = (current_game.size * current_game.size) - temp;
    current_game.turn = turn;
}

#endif