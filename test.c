/*#include <stdio.h>

#define MAX_SIZE_OF_STACK 30

#define MAX_PLAYERS_TO_PRINT 10

#define MAX_NAME_LENGHT 20

#define MAX_SIZE_OF_ARRAY 10

typedef struct {
   char name[MAX_NAME_LENGHT];
   int score;
   int number_of_moves;
} player;

typedef struct {
   short int n;
   char array_of_row_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   char array_of_column_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   char array_of_boxes[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
   double elapsed_time;
   char turn;
   int number_of_remaining_boxes;
   player player_1;
   player player_2;
   short int previous_sum;

} game;

typedef struct {
   game array[MAX_SIZE_OF_STACK];
   int top;
} Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;

int number_of_filled_boxes()
{
    // int n, char array[n][n] of boxes
    int sum = 0;

    for (int i = 0; i < current_game.n; ++i)
    {
        for (int j = 0; j < current_game.n; ++j)
        {
            sum += current_game.array_of_boxes[i][j] - '0';
        }
    }

    return sum;
}

void switch_turn()
{
    if(number_of_filled_boxes() == current_game.previous_sum)
    {
        //empty(&undo_stack);
        //empty(&redo_stack);
        current_game.turn = (current_game.turn == '1') ? '2' : '1'; /*1 and 2 or a and b*/ //modify the condition
/*
int main()
{
    game current_game;
    current_game.turn = '1';
    current_game.n = 3; // Adjust the size accordingly

    // Initialize array_of_boxes with some values for testing
    for (int i = 0; i < current_game.n; ++i) {
        for (int j = 0; j < current_game.n; ++j) {
            current_game.array_of_boxes[i][j] = '1';
        }
    }

    current_game.previous_sum = 9;
    switch_turn();
    printf("NEW: %c", current_game.turn);
}*/

/**#include <stdio.h>
int main(){

unsigned short int n ;

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

input_size() ;
//printf("\n %hu \n",n) ;
//printf("%d",*temp) ;
printf("size = %hu\n",n) ;
}*/

#include <stdio.h>
unsigned short int absolute(unsigned short int x){
    if(x<0){
        return -1*x ;
    }else{
        return x ;
    }
}

unsigned short int min(unsigned short int x,unsigned short int y){
    if(x<y){
        return x ;
    }else{
        return y ;
    }
}

unsigned short int n = 3 ;

unsigned short int check_node(char x){
   if (
       (int)x <= 57 && (int)x >= 49 && // integer
       (int)x<=(n+49) //positive & less than size
       ){
         return 1;
       }else{
         return 0 ;}
}

char row_edges[4][3] = {
    {'1','0','0'},
    {'2','1','0'},
    {'1','0','2'},
    {'0','2','1'}
};
char col_edges[3][4] = {
    {'1','2','1','0'},
    {'1','0','2','0'},
    {'1','2','0','1'}
};
char turn = '1';

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
         (absolute(r1-r2)==1 || absolute(c1-c2)==1)  //short line not long line
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
int main(){

input_nodes() ;

}
