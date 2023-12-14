#include <stdio.h>
//#include <C:\COLLEGE\Programming\Dots & Boxes\Display.h>

#define black "\e[1;30m"
#define red "\e[1;31m"
#define green "\e[1;32m"
#define High_intensity_green "\e[1;92m"
#define yellow "\e[1;33m"
#define blue  "\e[1;34m"
#define cyan "\e[1;36m"
#define High_intensity_cyan "\e[1;96m"
#define white "\e[1;37m"
#define High_intensity_white "\e[1;97m"

#define line "_______"

/******************************** بسم الله الرحمن الرحيم  ************************************/

/**player 1 ---> cyan , name1
player 2 ---> green , name2
dots ---> white

line constant --> 7 underscores _
space ---> '\t' --> 7 spaces

/** Names of variables
row_edges ---> 2D array of the edges of rows  ( of size [n+1][n])
col_edges ---> 2D array of the edges of columns ( of size[n][n+1])
boxes ---> 2D array of access of boxes and who close every box ( of size[n][n] )
number of dots  = (n+1)(n+1)
indexes of loops names ---> i,j,k
**/

void print_horizontal(int r,int n,int row_edges[][n]){
int i ; ///r is not index , if r=2 ---> row that has index 1
   for(i=0 ; i<n ; i++){
      printf(High_intensity_white".") ;

      if (row_edges[r-1][i] == 1){
         printf(High_intensity_cyan"%s",line) ;

      }else if(row_edges[r-1][i] == 2){
         printf(High_intensity_green"%s",line) ;

      }else{
         printf("\t") ;
      }
   }
   printf(High_intensity_white".\n") ;
}

void print_vertical(int c,int n,int col_edges[][n+1]){
   int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<n ; i++){
         if (col_edges[c-1][i]==1){
            printf(cyan"|");
            printf("\t") ;

         }else if(col_edges[c-1][i]==2){
            printf(green"|");
            printf("\t") ;

         }else{
            printf(" \t") ;
         }
      }
   if (col_edges[c-1][i]==1){
      printf(cyan"|\n");
   }else if(col_edges[c-1][i]==2){
      printf(green"|\n") ;
   }else{
      printf(" \n") ;
      }
   }
}

void print_grid(int n){
   int j ;
   for(j=1 ; j<=n ; j++){
      print_horizontal(j,n,row_edges) ;
      print_vertical(j,n,col_edges) ;
   }
   print_horizontal(j,n,row_edges) ;
}

void menu(){
   int x,y ;
   printf("Welcome to Dots & Boxes game\n") ;
   printf("Choose Beginner or Expert : ") ;
}
