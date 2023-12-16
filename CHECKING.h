#include <stdio.h>
#include <C:\COLLEGE\Programming\Dots-and-Boxes\Basic Var. & Func.h>

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

int check_boxes(short int boxes,int size){
   int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         //if(boxes[i][j]){

         }
      }
}

