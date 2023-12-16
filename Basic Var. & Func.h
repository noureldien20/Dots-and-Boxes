#include <stdio.h>
#include <stdlib.h>

/******************************** بسم الله الرحمن الرحيم  ***********************************/

#define red "\e[1;31m"
#define green "\e[1;32m"
#define yellow "\e[1;33m"
#define blue "\e[1;34m"
#define cyan "\e[1;36m"
#define white "\e[1;37m"
#define back_cyan "\e[46m"
#define back_green "\e[42m"
#define back_white "\e[47m"

/** Names of variables
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k **/

short int n ;
char **row_edges ;  //2D array of the edges of rows  ( of size [n+1][n])
char **col_edges ;  //2D array of the edges of columns ( of size[n][n+1])
char **boxes ;  //2D array of access of boxes and who close every box ( of size[n][n] )
char turn ;


void zero_array_2D(short int row,short int col,char arr[][]){
   for (int i=0 ; i<row ; i++){
      for (int j=0 ; j<col ; j++){
         *(*(arr + i)) + j = '0' ; }
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

char *create_array(short int row,short int col,char arr[][]){
   
   arr = malloc((row * col)*sizeof(char)) ;
   zero_array_2D(row ,col , char arr[][col]) ;
   return arr ;
}

void declare_arrays(short int n){
   row_edges = create_array(n+1,n,row_edges) ;
   col_edges = create_array(n,n+1,col_edges) ;
   boxes = create_array(n,n,boxes) ;
}