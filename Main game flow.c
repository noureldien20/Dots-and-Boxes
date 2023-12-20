#include <stdio.h>
#include <stdlib.h>
#include "Basic Var. and Func.h"
#include "INPUT.h"
#include "Display.h"

/******************************** بسم الله الرحمن الرحيم  *********************************/

int main(){

declare_arrays(3) ; //after entering size
printf("To Start game [Press S]\nTo load previous game [Press L]\n--------------> ") ;
char *g = malloc(sizeof(char)) ; 
scanf("%c",&g) ;
if(lower(g) == 'l'){
    // get data from saved file
    print_grid(n) ;
}

printf("test") ;






}
