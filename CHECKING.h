#include <stdio.h>
//#include <C:\COLLEGE\Programming\Dots & Boxes\CHECKING.h>

/******************************** بسم الله الرحمن الرحيم  **************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
**/

void check_n_print(int){

}

void check_edges(){
   for (i=0 ; i<n-1 ; i++){
      for (j=0 ; j<n-1 ; j++){
         if (row_edges[i+1][j] & row_edges[i+1][j] &&
         col_edges[i][j] & col_edges[i][j+1]){
           boxes[i][j] = '1' ; }
      }
   }
}

int check_boxes(int boxes,int size){
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if(boxes[i][j]){

         }
      }
   }
}

int input()
