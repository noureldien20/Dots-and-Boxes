void check_edges(){
   short int i,j ;
   for (i=0 ; i<n-1 ; i++){
      for (j=0 ; j<n-1 ; j++){
         if (row_edges[i+1][j] & row_edges[i+1][j] &&
            col_edges[i][j] & col_edges[i][j+1]){
           
           boxes[i][j] = (int)turn ;
         }
      }
   }
}