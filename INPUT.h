#include <stdio.h>
#include "Basic Var. and Func.h"

short int e1,e2 ;

void input_edge(){

    scanf("%d",&e1) ; //scanf("%c") ;
    scanf("%d",&e2) ; //scanf("%c") ;

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

