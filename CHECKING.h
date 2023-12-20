#ifndef CHECKING_H
# define CHECKING_H

#include <stdio.h>
#include "Basic Var. and Func.h"

/******************************** بسم الله الرحمن الرحيم  **************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
**/

void check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='0' && row_edges[i+1][j]!='0' &&
             col_edges[i][j]!='0' && col_edges[i][j+1] !='0'){
           
           boxes[i][j] = turn ;
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

void DFS(short int a,short int b){
   if (check_box(a,b)){

      if(dfs[a-1][b]=='0' && a-1<n && b<n){
         DFS(a-1,b) ;  // go up
         dfs[a-1][b] = '1' ;
      }
      if(dfs[a+1][b]=='0' && a+1<n && b<n){
         DFS(a+1,b) ;  // go down
         dfs[a+1][b] = '1' ;
      }
      if(dfs[a][b-1]=='0' && a<n && b-1<n){
         DFS(a,b-1) ;  // go <--- left
         dfs[a][b-1] = '1' ;
      }
      if(dfs[a][b+1]=='0' && a+1<n && b+1<n){
         DFS(a,b+1) ;  // go ---> right
         dfs[a][b+1] = '1' ;
      }
   
   }
}




#endif