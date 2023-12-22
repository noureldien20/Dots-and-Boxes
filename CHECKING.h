#ifndef CHECKING_H
#define CHECKING_H

#include <stdio.h>
#include "Basic Var. and Func.h"

/******************************** بسم الله الرحمن الرحيم  **************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
**/

// [INDICATOR]  row ---> 1  ,  column ---> 2
// n_empty = (n_edges/2) - 2

unsigned short int n_edges ; //number of filled edges in chain
unsigned short int n_empty ; //number of empty edges in chain

short int check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='\0' && row_edges[i+1][j]!='\0' &&
             col_edges[i][j]!='\0' && col_edges[i][j+1] !='\0' &&
             boxes[i][j] == '\0'){
           
            boxes[i][j] = turn ;
            return 1 ;
         }
      }
   }
}

short int check_box(short int i,short int j){
   short int n_zeros = 0 ;
   if(boxes[i][j] != '0'){

      if(row_edges[i][j] == '0'){n_zeros++ ; }
      if(row_edges[i][j+1] == '0'){n_zeros++ ; }
      if(col_edges[i][j] == '0'){n_zeros++ ; }
      if(col_edges[i+1][j] == '0'){n_zeros++ ; }

      if(row_edges[i][j] == '0' && n_zeros==1){
         row_edges[i][j] == turn ;
      }
      if(row_edges[i][j+1] == '0' && n_zeros==1){
         row_edges[i][j+1] == turn ;
      }
      if(col_edges[i][j] == '0' && n_zeros==1){
         col_edges[i][j] == turn ;
      }
      if(col_edges[i+1][j] == '0' && n_zeros==1){
         row_edges[i+1][j] == turn ;
      }

      if(n_zeros==1){
         boxes[i][j] == turn ;
         return 1 ;
      }else{
         return 0 ;
      }
   
   }
}


unsigned short int trace_vertical(){
   unsigned short int a,b;
   while(col_edges[a][b]!='0' && col_edges[a][b+1]!='0'){
      n_edges+=2 ;
      dfs[a][b] = turn ;
      a++ ;
   }


   return //index of the empty edge ;
}

unsigned short int trace_horizontal(){
   unsigned short int a,b;
   while(row_edges[a][b]!='0' && row_edges[a+1][b]!='0' && ){
      n_edges+=2 ;
      dfs[a][b] = turn ;
      b++ ;
   }

   return //index of the empty edge ;
}

void DFS(unsigned short int indicator,unsigned short int i,unsigned short int j){
   zero_2D_array(n,n,dfs) ;
   n_edges = 4 ; n_empty = 0;


}




#endif