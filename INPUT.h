#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include "Basic Var and Func.h"


int min(int a, int b)
{
    return (a < b) ? a : b;
}

void input_size(){

   char temp[5] = {'\0'};
   unsigned short int arr[2] = {0,0};

   printf("Enter size of grid [MAX %d]: ", MAX_GRID_SIZE) ;
    scanf("%2s",temp);

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
      clearInputBuffer();
      input_size() ;
   }
}

unsigned short int check_node(char x){
   if ((int)x <= 57 && (int)x >= 49){ // integer
         return 1;
       }else{
         return 0 ;
      }
}

void input_nodes(){ //bta3t ahmed
    unsigned short int r1,r2,c1,c2;
    printf("Enter 2 dots (row,row,col,col), for options [Press o]: ");

    char temp[10] = {'\0'};
    scanf("%4s",temp);

    if(temp[0] == 'o' || temp[0] == 'O'){
        clearInputBuffer();
        print_options();
        return;
    }

    if(!(check_node(temp[0]) && check_node(temp[1]) && check_node(temp[2]) && check_node(temp[3]))){
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    r1 = (unsigned short int)temp[0] - 48 ;
    r2 = (unsigned short int)temp[1] - 48 ;
    c1 = (unsigned short int)temp[2] - 48 ;
    c2 = (unsigned short int)temp[3] - 48 ;

    if(r1>n+1 || r2>n+1 || c1>n+1 || c2>n+1){
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    if(
        !(r1==r2 || c1==c2) ||   //nodes are adjacent
        !(abs(r1-r2)==1 || abs(c1-c2)==1) //short line not long line
        ){
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    if(r1==r2){
        if(row_edges[r1-1][min(c1,c2)-1]!='\0')
        {
            printf("Invalid input\n") ;
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(c1==c2){
        if(col_edges[min(r1,r2)-1][c1-1]!='\0'){         
            printf("Invalid input\n");
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(r1==r2){
        row_edges[r1-1][min(c1,c2)-1] = turn ;
        indexes[0] = r1-1 ;
        indexes[1] = min(c1,c2)-1 ;
        indexes[3] = 0 ;
    }
    else{ //c1==c2
        col_edges[min(r1,r2)-1][c1-1] = turn ;
        indexes[0] = min(r1,r2)-1 ;
        indexes[1] = c1-1 ;
        indexes[3] = 1 ;
    }
}

void AI_input(){
   
   /* precendence in input edges
   1. edges that will fill a box (box have 3 filled edges)
   2. edges in boxes that have 1 edge & make a chain
   3. edges in boxes that have 1 edge
   4. edges in a box that has zero edges filled [random] */  

   for(int i=0 ; i<n ; i++){ //box have 3 edges
      for(int j=0 ; j<n ; j++){
         if(boxes[i][j]=='\0'){
            
            if(row_edges[i][j]=='\0' && row_edges[i+1][j]!='\0' &&
               col_edges[i][j]!='\0' && col_edges[i][j+1]!='\0'){
               row_edges[i][j] = turn ; return ;
            }
            if(row_edges[i][j]!='\0' && row_edges[i+1][j]=='\0' &&
               col_edges[i][j]!='\0' && col_edges[i][j+1]!='\0'){
               row_edges[i+1][j] = turn ; return ;
            }
            if(row_edges[i][j]!='\0' && row_edges[i][j]!='\0' &&
               col_edges[i][j]=='\0' && col_edges[i][j+1]!='\0'){
               col_edges[i][j] = turn ; return ;
            }
            if(row_edges[i][j]!='\0' && row_edges[i][j]!='\0' &&
               col_edges[i][j]!='\0' && col_edges[i][j+1]=='\0'){
               col_edges[i][j+1] = turn ; return ;
            }

         }
      }
   }
}

void inputGameMode() 
{
    char temp[3];

    printf("Enter mode [0 for 2 Players, 1 for 1 Player]: ");

    if (scanf("%1s", temp) != 1 || (strcmp(temp, "0") != 0 && strcmp(temp, "1") != 0)) 
    {
        printf("Invalid input\n");
        clearInputBuffer();
        inputGameMode();
    } 
    else 
    {
        current_game.mode = temp[0] - '0';
    }
}



#endif