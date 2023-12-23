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

// n_empty = (n_edges/2) - 2

short int n_edges=3 ; //number of filled edges in chain
short int n_empty=1 ; //number of empty edges in chain
short int indexes[2] = {0,0} ;
short int director ;  // [director]  up or right ---> 1 , down or left ---> -1

short int check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='\0' && row_edges[i+1][j]!='\0' &&
             col_edges[i][j]!='\0' && col_edges[i][j+1] !='\0' &&
             boxes[i][j] == '\0'){
           
            //DFS() ;
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


short int n_edges=3 ; //number of filled edges in chain
short int n_empty=1 ; //number of empty edges in chain
unsigned short int indexes[2] = {0,0} ;
short int director ;  // [director]  up or right ---> 1 , down or left ---> -1

void trace_vertical(unsigned short int a,unsigned short int b,short int d){

   while(col_edges[a][b]!='\0' && col_edges[a][b+1]!='\0' && a<n && a>=0){
      n_edges+=2 ;
      dfs[a][b] = turn ;
      a = a-d ;

      if(row_edges[a-d][b]!='\0'){
         n_edges++ ;
         director = 0 ;
         dfs[a][b] = turn ;
         break ;
      }
      n_empty++ ;
   }

   if(director){
      if(col_edges[a][b]!='\0'){
         n_edges++;
         director = 1 ;
         n_empty++ ;
      }else if(col_edges[a][b+1]!='\0'){
         n_edges++;
         director = -1 ;
         n_empty++ ;
      }else{ //No chain
         director = 0;
         n_empty++ ;
      }

   }
}

unsigned short int trace_horizontal(){
   unsigned short int a,b;
   while(row_edges[a][b]!='\0' && row_edges[a+1][b]!='\0'){
      n_edges+=2 ;
      dfs[a][b] = turn ;
      b++ ;
   }

}

void DFS(unsigned short int i,unsigned short int j){
   indexes[0] = i ; indexes[1] = j;
   //zero_2D_array(n,n,dfs) ;
   while(director){
      //trace_horizontal();
      trace_vertical(indexes[0],indexes[1],-1) ;
   }

   if(n_empty == (n_edges/2) - 2){
      printf("chain\n") ;
      //make dfs equal to row_edges, col_edges, boxes
   }else{
      printf("not chain\n") ;
      n_edges = 0 ;
      n_empty = 0 ;

   }

}






#endif