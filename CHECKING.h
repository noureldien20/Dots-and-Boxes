#ifndef CHECKING_H
#define CHECKING_H

#include "INPUT.h"
#include "Basic Var and Func.h"

/******************************** بسم الله الرحمن الرحيم  **************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
**/

// n_empty = (n_edges/2) - 2

// sign = 0 (director = 1 , -2)
// sign = 1 (director = -1 , 2)

//el function ely enta 3ayzha ya zmyly
void generate_edges(){
    for(int i = 0 ; i < n  ; i++){
        for(int j = 0 ; j < n  ; j++){
            if(dfs[i][j] == '1'){
               
               row_edges[i][j] = turn;
               row_edges[i + 1][j] = turn;
               col_edges[i][j] = turn;
               col_edges[i][j + 1] = turn;
               boxes[i][j] = turn ;
            }
        }
    }
}

void check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='\0' && row_edges[i+1][j]!='\0' &&
             col_edges[i][j]!='\0' && col_edges[i][j+1] !='\0' &&
             boxes[i][j] == '\0'){
           
            //DFS() ;
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

void directing(){   
   
   if(indexes[2] == 0){ // edge is row
      if(indexes[0] == 0 || indexes[0] == n){director = 0 ;}
      else if (boxes[indexes[0]][indexes[1]] != '\0'){director = -1 ;}
      else{director = 1 ;}
   
   }else{ // edge is column
      if(indexes[1] == 0 || indexes[1] == n){director = 0 ;}
      else if (boxes[indexes[0]][indexes[1]] != '\0'){director = 2 ;}
      else{director = -2 ;}
   }

}

void trace_vertical(short int a,short int b,unsigned int sign){
   while(a<n && a>=0 && col_edges[a][b]!='\0' && col_edges[a][b+1]!='\0'){
      n_edges+=2 ;
      dfs[a][b] = turn ;

      if(row_edges[a+sign][b]!='\0'){
         n_edges++ ;
         director = 0 ;
         dfs[a][b] = turn ;
         break ;
      }

      a = a-director ;
      n_empty++ ;
   }

   if(director){
      if(col_edges[a][b] == '\0' && row_edges[a+sign][b]!='\0'){
         n_edges+=2 ; n_empty++ ;
         director = -2 ;
         indexes[0] = a ; indexes[1] = b ;
         dfs[a][b] = turn ;
      }else if(col_edges[a][b+1] =='\0' && row_edges[a+sign][b]!='\0'){
         n_edges+=2 ; n_empty++ ;
         director = 2 ;
         indexes[0] = a ; indexes[1] = b+1 ;
         dfs[a][b] = turn ;
      }else{ //No chain
         director = 0 ;
         n_empty++ ;
      }

   }
}

void trace_horizontal(short int a,short int b,unsigned int sign){
   director = director / 2 ;
   while(b<n && b>=0 && row_edges[a][b]!='\0' && row_edges[a+1][b]!='\0'){
      n_edges+=2 ;
      dfs[a][b] = turn ;

      if(col_edges[a][b+sign]!='\0'){ 
         n_edges++ ;
         director = 0 ;
         dfs[a][b] = turn ;
         break ;
      }

      b = b+director ;
      n_empty++ ;
   }

   if(director){

      if(row_edges[a][b] == '\0' && col_edges[a][b+sign]!='\0'){
         n_edges+=2 ; n_empty++ ;
         director = 1 ;
         indexes[0] = a ; indexes[1] = b ;
         dfs[a][b] = turn ;
      }else if(row_edges[a+1][b] =='\0' && col_edges[a][b+sign]!='\0'){
         n_edges+=2 ; n_empty++ ;
         director = -1 ;
         indexes[0] = a+1 ; indexes[1] = b ;
         dfs[a][b] = turn ;

      }else{ //No chain
         director = 0 ;
         n_empty++ ;
      }

   }
}

void DFS(){
   //directing();
   while(director){

      if(director == 1){
         trace_vertical(indexes[0]-1,indexes[1],0) ;

      }else if(director == -1){
         trace_vertical(indexes[0],indexes[1],1) ;

      }else if(director == 2){
         trace_horizontal(indexes[0],indexes[1],1) ;

      }else{  // director == -2
         trace_horizontal(indexes[0],indexes[1]-1,0) ;
      }

   }

   if(n_empty == (n_edges/2) - 2){
      generate_edges();
      //make dfs equal to row_edges, col_edges, boxes
   }

   n_edges = 3 ;
   n_empty = 1 ;
   zero_2D_array(n,n,dfs) ;
}





#endif