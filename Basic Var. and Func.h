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

#define Ctrl+Z '\x1A'
#define Ctrl+R '\x12'
#define Ctrl+S '\x13'

/** Names of variables
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k **/

short int n ;
char **row_edges ;  //2D array of the edges of rows  ( of size [n+1][n])
char **col_edges ;  //2D array of the edges of columns ( of size[n][n+1])
char **boxes ;  //2D array of access of boxes and who close every box ( of size[n][n] )
char **dfs ;
char turn ;
//int score1 , score2 ;  // Scores of players


void zero_2D_array(short int row,short int col,char arr[][]){
   for (int i=0 ; i<row ; i++){
      for (int j=0 ; j<col ; j++){
         arr[i][j] = '0' ; }
   }
}

void print_array_2D(short int row,short int col,char arr[][]){
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

void declare_arrays(short int n){
   char **row_edges = create_array(n+1,n) ;
   char **col_edges = create_array(n,n+1) ;
   char **boxes = create_array(n,n) ;
   char **dfs = create_array(n,n) ;
}

char small(char c){
   if (c>=65 && c<=90){ return c+32 ; }
   else{return c ;}
}

char big(char c){
   if (c>=97 && c<=122){ return c-32 ; }
   else{return c ;}
}

#endif