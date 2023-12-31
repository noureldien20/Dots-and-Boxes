#ifndef CHECKING_H
#define CHECKING_H

#include "INPUT.h"
#include "Basic_Var_and_Func.h"

void trace_horizontal(short int a,short int b,unsigned short int sign);
void DFS() ;

/***************************************** بسم الله الرحمن الرحيم  ********************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
**/

short int n_edges = 3 ; //number of filled edges in chain
short int n_empty = 1 ; //number of empty edges in chain

short int director = 0 ;  // [director]  up ---> 1 , down ---> -1
// [director]  right ---> 2 , left ---> -2

// sign = 0 (director = 1 , -2)
// sign = 1 (director = -1 , 2)

//el function ely enta 3ayzha ya zmyly
void generate_edges(){
    for(int i = 0 ; i < n  ; i++){
        for(int j = 0 ; j < n  ; j++){
            if(dfs[i][j] != '\0'){
               
               row_edges[i][j] = turn;
               row_edges[i + 1][j] = turn;
               col_edges[i][j] = turn;
               col_edges[i][j + 1] = turn;
               boxes[i][j] = turn ;
            }
        }
    }
}

void directing(){
   if(indexes[2] == 0){ // edge is row
      if(indexes[0]==0 || indexes[0]==n){
         director = 0 ;

      }else if(boxes[indexes[0]][indexes[1]]!='\0'){
         director = 1 ;

      }else{
         director = -1 ;
      }
   
   }else{ // edge is column
      
      if(indexes[1] == 0 || indexes[1] == n){
         director = 0 ;

      }else if(boxes[indexes[0]][indexes[1]-1] != '\0'){
         director = 2 ;

      }else{
         director = -2 ;
      }
   }

  //printf("\n director = %hd \n", director) ;

}

void check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='\0' && row_edges[i+1][j]!='\0' &&
             col_edges[i][j]!='\0' && col_edges[i][j+1] !='\0' &&
             boxes[i][j] == '\0'){
            
            //printf("indexes  (%hd , %hd)",indexes[0],indexes[1]);
            boxes[i][j] = turn ;
            directing() ;
            DFS() ;
            boxes[i][j] = turn ;
         }
      }
   }
}

void trace_vertical(short int a,short int b,unsigned short int sign){
   if(a>n-1 || b>n || a<=0 || b<0 || dfs[a+sign-1][b]!='\0'){return;}

   while(a<n && a>0 && col_edges[a+sign-1][b]!='\0' && col_edges[a+sign-1][b+1]!='\0'){
      n_edges+=2 ;
      dfs[a+sign-1][b] = turn ;
      if(row_edges[a+sign+sign-1][b]!='\0'){
         n_edges++ ;
         director = 0 ;
         dfs[a+sign-1][b] = turn ;
         break ;
      }
      a = a-director ;
      n_empty++ ;
   }

   if(director){

      if(col_edges[a+sign-1][b+1] =='\0' && row_edges[a-director][b]!='\0' && col_edges[a+sign-1][b] != '\0'){
         // Letter L
         n_edges+=2 ; n_empty++ ;
         dfs[a+sign-1][b] = turn ;

         director = 2 ;
         trace_horizontal(a+sign-1,b+1,1) ;

      }else if(col_edges[a+sign-1][b+1] != '\0' && row_edges[a-director][b]!='\0' && col_edges[a+sign-1][b] =='\0'){
         // Inverted L
         n_edges+=2 ; n_empty++ ;
         dfs[a+sign-1][b] = turn ;

         director = -2 ;
         trace_horizontal(a+sign-1, b,0) ;

      }else if(col_edges[a+sign-1][b+1] == '\0' && row_edges[a-director][b]=='\0' && col_edges[a+sign-1][b] !='\0'){
         // L opened from bottom
         short int old_director = director ;
         n_edges+=1 ; n_empty+=2 ;
         dfs[a+sign-1][b] = turn ;

         director = 2 ;
         trace_horizontal(a+sign-1,b+1,1) ;

         director = old_director ;
         trace_vertical(a-director,b,sign) ; // continue tracing in original path

      }else if(col_edges[a+sign-1][b+1] != '\0' && row_edges[a-director][b]=='\0' && col_edges[a+sign-1][b] =='\0'){
         // Inverted L opened from bottom
         short int old_director = director ;
         n_edges++ ; n_empty+=2 ;

         director = -2 ;
         dfs[a+sign-1][b] = turn ;
         trace_horizontal(a+sign-1,b,0) ;

         director = old_director ;
         trace_vertical(a-director,b,sign) ; // continue tracing in original path

      }else{ // plus chain
         short int old_director = director ;
         n_empty+=3 ;
         //printf("\nn_edges = %d , n_empty = %d\n", n_edges, n_empty) ;
         director = 2 ;
         dfs[a+sign-1][b] = turn ;
         trace_horizontal(a+sign-1,b+1,1) ;

         director = -2 ;
         dfs[a+sign-1][b] = turn ;
         trace_horizontal(a+sign-1,b,0) ;
         
         if(row_edges[a-old_director][b]!='\0'){
            n_empty-- ; n_edges++ ; return ;
         }

         director = old_director ;
         trace_vertical(a-director,b,sign) ; // continue tracing in original path
         //printf("\nn_edges = %d , n_empty = %d\n", n_edges, n_empty) ;
      }

   }
}

/*******************************************************************************************************************************/

void trace_horizontal(short int a,short int b,unsigned short int sign){

   director = director / 2 ;
   if(a>n || b>n-1 || a<0 || b<=0 || dfs[a][b+sign-1]!='\0'){return;}

   while(b<n && b>0 && row_edges[a][b+sign-1]!='\0' && row_edges[a+1][b+sign-1]!='\0'){
      n_edges+=2 ;
      dfs[a][b+sign-1] = turn ;

      if(col_edges[a][b+sign+sign-1]!='\0'){ 
         n_edges++ ;
         director = 0 ;
         dfs[a][b+sign-1] = turn ;
         return ;
      }

      b = b+director ;
      n_empty++ ;
   }

   if(director){

      if(row_edges[a][b+sign-1] == '\0' && row_edges[a+1][b+sign-1]!='\0' && col_edges[a][b+director] != '\0'){
         // half inverted T
         n_edges+=2 ; n_empty++ ;
         dfs[a][b+sign-1] = turn ;

         director = 1 ;
         trace_vertical(a,b+sign-1,0) ; // trace up only

      }else if(row_edges[a][b+sign-1] != '\0' && row_edges[a+1][b+sign-1]=='\0' && col_edges[a][b+director] != '\0'){
         // half T
         n_edges+=2 ; n_empty++ ;
         dfs[a][b+sign-1] = turn ;

         director = -1 ;
         trace_vertical(a+1,b+sign-1,1); // trace down only

      }else if(row_edges[a][b+sign-1] != '\0' && row_edges[a+1][b+sign-1]=='\0' && col_edges[a][b+director] == '\0'){
         // T chain
         short int old_director = director*2 ;
         n_edges+=1 ; n_empty+=2 ;
         dfs[a][b+sign-1] = turn ;

         director = -1 ;
         trace_vertical(a+1,b+sign-1,1) ; // trace down 

         director = old_director ;
         trace_horizontal(a,b+(director/2),sign) ; // continue tracing in original path

      }else if(row_edges[a][b+sign-1] == '\0' && row_edges[a+1][b+sign-1]!='\0' && col_edges[a][b+director] == '\0'){
         // Inverted T chain
         //printf("here\n");
         short int old_director = director*2 ;
         n_edges++ ; n_empty+=2 ;
         dfs[a][b+sign-1] = turn ;

         director = 1 ;
         trace_vertical(a,b+sign-1,0) ; // trace up

         director = old_director ;
         //printf("\nhere with a = %d , b = %d , director = %d\n",a,b,director);
         trace_horizontal(a,b+(director/2),sign) ; // continue tracing in original path

      }else{ // plus chain
         short int old_director = director*2 ;
         dfs[a][b+sign-1] = turn ;
         n_empty+=3 ;

         director = 1 ;
         trace_vertical(a,b+sign-1,0) ; // trace up

         director = -1 ;
         trace_vertical(a+1,b+sign-1,1) ; // trace down

         //printf("\nin dfs and old director = %hd , a = %hd , b = %hd\n",old_director,a,b);
         //printf("\nn_edges = %d , n_empty = %d\n", n_edges, n_empty) ;
         if(col_edges[a][b+(old_director/2)] != '\0'){
            n_empty-- ; n_edges++ ; return ;
         }

         director = old_director ;
         trace_horizontal(a,b+(director/2),sign) ; // continue tracing in original path*/
      }

   }

}

void DFS(){
   printf("\nhere with a = %d , b = %d , director = %d\n",indexes[0],indexes[1],director);

   if(!director)
   {
      return;
   }
   
   if(director == 1){
      trace_vertical(indexes[0],indexes[1],0) ;

   }else if(director == -1){
      trace_vertical(indexes[0],indexes[1],1) ;

   }else if(director == 2){
      trace_horizontal(indexes[0],indexes[1],1) ;

   }else{  // director == -2
      trace_horizontal(indexes[0],indexes[1],0) ;
   }
   
   if(n_empty == (n_edges/2) - 2){
      generate_edges() ;
   }
   n_edges = 3 ;
   n_empty = 1 ;
   zero_2D_array(n,n,dfs) ;

}



#endif