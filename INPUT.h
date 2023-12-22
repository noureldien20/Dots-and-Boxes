#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "Basic Var. and Func.h"

void input_size(){

   char temp[20] = {'\0'} ;
   unsigned short int arr[2] = {0,0};

   printf("Enter size of grid [MAX 29] : ") ;
   scanf("%s",temp) ;

   if(
      ( (int)temp[0] <= 57 && (int)temp[0] >= 49 && temp[1]=='\0' ||
      (int)temp[0] <= 50 && (int)temp[0] >= 49 && temp[1]!='\0' )
      &&(
         (int)temp[1] <= 57 && (int)temp[1] >= 48 || temp[1] == '\0'
        ) && (temp[2]=='\0')
     ){
      arr[0] = (unsigned short int)temp[0] - 48 ;

      if (temp[1]!='\0'){
         arr[1] = (unsigned short int)temp[1] - 48 ;
         n = arr[1] + (arr[0]*10) ;
      }else{
         n = arr[0] ;
      }

   }else{
      printf("Invalid input\n") ;
      input_size() ;
   }
}

unsigned short int check_node(char x){
   if (
       (int)x <= 57 && (int)x >= 49 && // integer
       (int)x<=(n+49) //positive & less than size
       ){
         return 1;
       }else{
         return 0 ;}
}

void input_nodes(){

   unsigned short int r1,r2,c1,c2;
   printf("Enter 2 dots (row,row , column,column) : ") ;

   char temp[20] = {'\0'} ;
   scanf("%s",temp) ;

   if( !(check_node(temp[0]) && check_node(temp[1]) &&
      check_node(temp[2]) && check_node(temp[3])) ){
         printf("Invalid input\n") ;
         input_nodes() ;
      }

   if(temp[4]=='\0'){

      r1 = (unsigned short int)temp[0]-48 ; r2 = (unsigned short int)temp[1]-48 ;
      c1 = (unsigned short int)temp[2]-48 ; c2 = (unsigned short int)temp[3]-48 ;

      if(!
         (r1==r2 || c1==c2) &&   //nodes are adjacent
         (abs(r1-r2)==1 || abs(c1-c2)==1)  //short line not long line
         ){
           printf("Invalid input\n") ;
           input_nodes() ;

      }else if(row_edges[r1-1][min(c1,c2)-1]!='0' && r1==r2 ||
               col_edges[min(r1,r2)-1][c1-1]!='0' && c1==c2){
                  
         printf("Invalid input\n") ;
         input_nodes() ;
      }else{

        if(r1==r2){
            row_edges[r1-1][min(c1,c2)-1] = turn ;
        }else{
            col_edges[min(r1,r2)-1][c1-1] = turn ;
        }

      }

   }else{
      printf("Invalid input\n") ;
      input_nodes() ;
   }
}

input_options(){

}


#endif