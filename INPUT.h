#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>

#include "Basic_Var_and_Func.h"
#include "Menu_Options.h"

void print_options();
void check_edges();

int min(int a, int b){
    return (a < b) ? a : b;
}

void input_size(){

    char *temp ;
    printf("Enter size of grid [MAX %d]: ", MAX_GRID_SIZE) ; // momken n5aly max 9 eshan el input 2arafny
    temp = take_input(2) ;

    if(temp[0] <= '9' && temp[0] > '0' && temp[1]=='\0'){
        n = temp[0] - 48 ;

    }else{
        printf(red"Invalid input\n"RESET) ;
        input_size();
    }
}

unsigned short int check_node(char x){
   if ((int)x <= 57 && (int)x >= 49){ // integer
         return 1;
       }else{
         return 0 ;
      }
}

void input_nodes()
{ //bta3t ahmed
    unsigned short int r1,r2,c1,c2;
    printf("Enter 2 dots (row,row,col,col), for options [Press o]: ");

    char* temp;
    char op ;
    temp = take_input(6);

    if((temp[0] == 'o' || temp[0] == 'O') && temp[1] == '\0')
    {
        print_options();
        return;
    }

    if(temp[4] != '\0' && !(check_node(temp[0]) && check_node(temp[1]) && check_node(temp[2]) && check_node(temp[3]))){
        printf(red"Invalid input\n"RESET) ;
        input_nodes() ;
        return;
    }

    r1 = (unsigned short int)temp[0] - 48 ;
    r2 = (unsigned short int)temp[1] - 48 ;
    c1 = (unsigned short int)temp[2] - 48 ;
    c2 = (unsigned short int)temp[3] - 48 ;

    if(r1>n+1 || r2>n+1 || c1>n+1 || c2>n+1){
        printf(red"Invalid input\n"RESET) ;
        input_nodes() ;
        return;
    }

    if(
        !(r1==r2 || c1==c2) ||   //nodes are adjacent
        !(abs(r1-r2)==1 || abs(c1-c2)==1) //short line not long line
        ){
        printf(red"Invalid input\n"RESET) ;
        input_nodes() ;
        return;
    }

    if(r1==r2){
        if(row_edges[r1-1][min(c1,c2)-1]!='\0')
        {
            printf(red"Invalid input\n"RESET) ;
            input_nodes() ;
            return;
        }
    }

    if(c1==c2){
        if(col_edges[min(r1,r2)-1][c1-1]!='\0'){         
            printf(red"Invalid input\n"RESET);
            input_nodes() ;
            return;
        }
    }

    if(r1==r2){
        row_edges[r1-1][min(c1,c2)-1] = turn ;
        
        indexes[0] = r1-1 ;
        indexes[1] = min(c1,c2)-1 ;
        indexes[2] = 0 ;

        check_edges();
        empty_redo_stack();
        UndoRedoFlag = 0;
    }
    else{ //c1==c2
        col_edges[min(r1,r2)-1][c1-1] = turn ;
        indexes[0] = min(r1,r2)-1 ;
        indexes[1] = c1-1 ;
        indexes[2] = 1 ;
        check_edges();
        empty_redo_stack();
        UndoRedoFlag = 0;
    }
}

void AI_input()
{
    /* precendence in input edges
    1. edges that will fill a box (box have 3 filled edges)
    2. edges in boxes that have 1 edge & make a chain
    3. edges in boxes that have 1 edge
    4. edges in a box that has zero edges filled [random] */  

    // Seed the random number generator with the current time
    srand(time(NULL));

    //box have 3 edges
    for(int i = 0 ; i < n ; i++)
    { 
        for(int j = 0 ; j < n ; j++)
        {
            if(boxes[i][j] == '\0')
            {
                if(row_edges[i][j] == '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] != '\0')
                {
                    row_edges[i][j] = turn;
                    return;
                }

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] != '\0')
                {
                    row_edges[i+1][j] = turn;
                    return;
                }

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] != '\0')
                {
                    col_edges[i][j] = turn;
                    return;
                }

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] == '\0')
                {
                    col_edges[i][j+1] = turn;
                    return;
                }
            }
        }
    }
  
    // box has 0 edge
    for(int i = 0 ; i < n ; i++)
    { 
        for(int j = 0 ; j < n ; j++)
        {
            if(boxes[i][j] == '\0')
            {
                int random_choice = rand() % 4;

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else if (random_choice == 1) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else if (random_choice == 2)
                    {
                        col_edges[i][j] = turn;
                    }
                    else
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return;
                }
            }
        }
    }

    // box has 1 edge
    for(int i = 0 ; i < n ; i++)
    { 
        for(int j = 0 ; j < n ; j++)
        {
            if(boxes[i][j] == '\0')
            {
                int random_choice = rand() % 3;

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else if (random_choice == 1) 
                    {
                        col_edges[i][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else if (random_choice == 1) 
                    {
                        col_edges[i][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else if (random_choice == 1) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] != '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else if (random_choice == 1) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j] = turn;
                    }
                    return;
                }
            }
        }
    }

    // box has 2 edges
    for(int i = 0 ; i < n ; i++)
    { 
        for(int j = 0 ; j < n ; j++)
        {
            if(boxes[i][j] == '\0')
            {
                int random_choice = rand() % 2;

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return ;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] != '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else 
                    {
                        row_edges[i+1][j] = turn;
                    }
                    return ;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] != '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return ;
                }

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] == '\0')
                {
                    if (random_choice == 0) 
                    {
                        col_edges[i][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j+1] = turn;
                    }
                    return ;
                }

                if(row_edges[i][j] != '\0' && row_edges[i+1][j] == '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] != '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i+1][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j] = turn;
                    }
                    return ;
                }

                if(row_edges[i][j] == '\0' && row_edges[i+1][j] != '\0' && col_edges[i][j] == '\0' && col_edges[i][j+1] != '\0')
                {
                    if (random_choice == 0) 
                    {
                        row_edges[i][j] = turn;
                    } 
                    else 
                    {
                        col_edges[i][j] = turn;
                    }
                    return ;
                }
            }
        }
    }
    
}

void inputGameMode() 
{
    char *temp ;
    printf("Enter mode [2 for 2 Players, 1 for 1 Player]: ");
    temp = take_input(2) ;
    printf("\n");

    if(temp[1]!='\0' || (temp[0]!='1' && temp[0]!='2')){
        printf(red"Invalid input\n"RESET);
        inputGameMode();
    }
    else 
    {
        current_game.mode = temp[0] - '0';
    }

}



#endif