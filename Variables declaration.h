#include <stdio.h>
/******************************** بسم الله الرحمن الرحيم  **************************************/

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k
**/

int n ;
int row_edges[n+1][n] ;
int col_edges[n][n+1] ;
int boxes[n][n] ;




void zero_array_2D(int row,int col,int arr[][col]){
   for (int i=0 ; i<row ; i++){
      for (int j=0 ; j<col ; j++){
         arr[i][j] = 0 ; }
   }
}

