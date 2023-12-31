#ifndef BASIC_VAR_AND_FUNC_H
#define BASIC_VAR_AND_FUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
//#include <pthread.h>

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
#define MAX_NAME_LENGTH 10
#define MAX_GRID_SIZE 9
#define MAX_SIZE_OF_STACK 15

typedef struct 
{
   char name[MAX_NAME_LENGTH + 1];
   int score;
   int number_of_moves;
} player;

typedef struct 
{
    short int index_flag;
    unsigned short int size;
    char array_of_row_edges[MAX_GRID_SIZE+1][MAX_GRID_SIZE];
    char array_of_column_edges[MAX_GRID_SIZE][MAX_GRID_SIZE+1];
    char array_of_boxes[MAX_GRID_SIZE][MAX_GRID_SIZE];
    unsigned int elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;
    unsigned short int mode; // 1 ( 1 player ) --> computer
} game;

game current_game;
game previous_state;

typedef struct {
    game array[MAX_SIZE_OF_STACK];
    int pointer_to_index ;
}Stack ;

Stack Game_stack ;

unsigned short int n ;
char **row_edges ;  //2D array of the edges of rows  ( of size [n+1][n])
char **col_edges ;  //2D array of the edges of columns ( of size[n][n+1])
char **boxes ;  //2D array of access of boxes and who close every box ( of size[n][n] )
char **dfs ;
char turn = '1' ;
int temp_time = 60 ; //add me to reset variables
int UndoRedoFlag ;

short int indexes[3] = {0,0,0} ;
//third element in indexes array express edge is row or col  [row ---> 0] , [col ---> 1]

// mode indicator
short int mode ;  // 1 --> computer

void empty_stack();
void push();

char *take_input(int length) {
    char c;
    char* s = malloc(length + 1);
    int i = 0;

    while((c = getchar()) != '\n')
    {
        if(i < length){
            s[i] = c;
            i++;
        }
    }

    s[i] = '\0';
    return s;
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

void declare_arrays()
{
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

    for (short int i = 0; i < n; ++i)
    {
        for (short int j = 0; j < n; ++j)
        {
            if (boxes[i][j] != '\0')
            {
                count++;
            }
        }
    }
    return count;
}

void time_passed(){
    while((number_of_filled_boxes()) != n*n){

        if(current_game.elapsed_time == temp_time){
            printf("\nTime:  %02d : %02d\n", current_game.elapsed_time / 60, current_game.elapsed_time % 60 );
            
        }

        //Sleep(1000) ;
        current_game.elapsed_time++; 
    }
}

void switch_turn()
{
    int temp = number_of_filled_boxes();

    if (current_game.turn == '1') 
    {
        current_game.player_1.number_of_moves++ ;
    }
    else 
    {
        current_game.player_2.number_of_moves++ ;
    }

    if(temp == current_game.previous_sum)
    {
        empty_stack();
        current_game.turn = (current_game.turn == '1') ? '2' : '1';
        turn = current_game.turn;
        //double_push_flag == 1;
    }
    else{
        if (current_game.turn == '1'){
            current_game.player_1.score += temp - current_game.previous_sum;
        } 
        else{
            current_game.player_2.score += temp - current_game.previous_sum;
        }
        // push only if he closes a box
        //push();
    }
    current_game.number_of_remaining_boxes = (current_game.size * current_game.size) - temp;
}

void copy_current_game_arrays_from_Ahmed() ;

void reset_variables_to_zeros()
{
    current_game.turn = '1';
    turn = '1';
    current_game.player_1.number_of_moves = 0;
    current_game.player_2.number_of_moves = 0;
    current_game.player_1.score = 0;
    current_game.player_2.score = 0;
    empty_stack();
    current_game.index_flag = 1 ;
    current_game.elapsed_time = 0 ; 
    copy_current_game_arrays_from_Ahmed();
}

void copy_current_game_arrays_to_Ahmed(){ 
    for (int i = 0; i < n ; i++){
        for (int j = 0; j < n ; j++){

            row_edges[i][j] = current_game.array_of_row_edges[i][j];
            col_edges[i][j] = current_game.array_of_column_edges[i][j];
            boxes[i][j] = current_game.array_of_boxes[i][j];
        }

        row_edges[n][i] = current_game.array_of_row_edges[n][i] ;
        col_edges[i][n] = current_game.array_of_column_edges[i][n];
    }
}

void copy_current_game_arrays_from_Ahmed(){
    for (int i = 0; i < n ; i++){
        for (int j = 0; j < n ; j++){

            current_game.array_of_row_edges[i][j] = row_edges[i][j] ;
            current_game.array_of_column_edges[i][j] = col_edges[i][j] ;
            current_game.array_of_boxes[i][j] = boxes[i][j] ;
        }

        current_game.array_of_row_edges[n][i] = row_edges[n][i] ;
        current_game.array_of_column_edges[i][n] = col_edges[i][n] ;
    }

}

#endif