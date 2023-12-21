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

void input_nodes(){
    int c1,r1,r2,c2 ;
    scanf("%d",&e1) ;
    scanf("%d",&e2) ;
    
    if(!
    (r1==r2 || c1==c2) &&   //nodes are adjacent
    (r1<=n && r2<=n && c1<=n && c2<=n) && // board has this index
    (abs(r1-r2)==1 || abs(c1-c2)==1) &&  //short line not long line
    (r1>0 && r2>0 && c1>0 && c2>0) //positve
    ){
        printf("Not valid\nEnter valid input : ") ;
        input_edge() ;
    
    }else{

        if(r1==r2){
            row_edges[r1-1][min(c1,c2)-1] = turn ;
        }else{
            col_edges[min(r1,r2)-1][c1-1] = turn ;
        }

    }
}

#endif