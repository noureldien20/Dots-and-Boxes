#include <stdio.h>
#include "Basic Var. & Func.h"

short int r1,r2,c1,c2 ;
char abs(char x){
    if(x<0){
        return -1*x ;
    }else{
        return x ;
    }
}

char min(char x,char y){
    if(x<y){
        return x ;
    }else{
        return y ;
    }
}

void input_edge(){

    scanf("%d",&r1) ; //scanf("%c") ;
    scanf("%d",&r2) ; //scanf("%c") ;
    scanf("%d",&c1) ; //scanf("%c") ;
    scanf("%d",&c2) ;

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

