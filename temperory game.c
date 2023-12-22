#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE_OF_STACK 30
#define MAX_PLAYERS_TO_PRINT 10
#define MAX_NAME_LENGHT 40
#define MAX_SIZE_OF_ARRAY 10
#define red "\e[0;31m"
#define green "\e[0;32m"
#define yellow "\e[0;33m"
#define blue "\e[0;34m"
#define cyan "\e[0;36m"
#define white "\e[0;37m"
#define back_cyan "\e[46m"
#define back_green "\e[42m"
#define back_white "\e[47m"
//#define Ctrl+Z '\x1A'
//#define Ctrl+R '\x12'
//#define Ctrl+S '\x13'
#define line "-------"
//#include <pthread.h>

typedef struct {
   char name[MAX_NAME_LENGHT + 1];
   int score;
   int number_of_moves;
} player;

typedef struct {
    unsigned short int size;
    char array_of_row_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_column_edges[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    char array_of_boxes[MAX_SIZE_OF_ARRAY][MAX_SIZE_OF_ARRAY];
    double elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;
    short int mode; // 1 --> computer
}game;

typedef struct {
    game array[MAX_SIZE_OF_STACK];
    int top;
} Stack;

Stack undo_stack;
Stack redo_stack;
game current_game;

unsigned short int n ;
char **row_edges ;
char **col_edges ;
char **boxes ;
char **dfs ;
char turn ;
//time_t time ;

char **create_array(short int row,short int col){
   char **arr = (char **)calloc(row, sizeof(char *)) ;
   
   for(short int i=0 ; i<row ; i++){
      arr[i] = (char *)calloc(col, sizeof(char));
   }
   return arr ;
}

void declare_arrays(short int n){
   row_edges = create_array(n+1,n) ;
   col_edges = create_array(n,n+1) ;
   boxes = create_array(n,n) ;
   //dfs = create_array(n,n) ;
}

void zero_2D_array(short int row,short int col,char **arr){

   for (int i=0 ; i<row ; i++)
   {
        for (int j=0 ; j<col ; j++)
        {
            arr[i][j] = '0' ; 
        }
   }
}

void print_array_2D(short int row,short int col,char **arr){
   for (short int i=0 ; i<row ; i++){
      for (short int j=0 ; j<col ; j++){
      printf("%c ",arr[i][j]);
      }
      printf("\n");
   }
}

void print_horizontal(short int r){
   short int i ;   ///r is not index , if r=2 ---> row that has index 1
   for(i=0 ; i<n ; i++){
        printf(white"+") ;
        //printf("%hd", r);
        //print_array_2D(n+1,n, row_edges);
        
        if (row_edges[r-1][i] == '1'){
            printf(cyan"%s",line) ;
        }else if(row_edges[r-1][i] == '2'){
            printf(green"%s",line) ;
        }else{
            printf("       ") ;
        }
   }
   printf(white"+\n") ;
}

void print_boxes_color(short int c,short int i){
   if (boxes[c-1][i]=='1'){
      printf(back_cyan"       ") ;
   }else if(boxes[c-1][i]=='2'){
      printf(back_green"       ") ;
   }else{
      printf("       ") ;
   }
}

void print_vertical(short int c){
   int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<n ; i++){

         if(col_edges[c-1][i] =='1' || boxes[c-1][i] == '1'){
            printf(cyan"|") ;
         }else if(col_edges[c-1][i] =='2' || boxes[c-1][i] == '2'){
            printf(green"|") ;
         }else{
            printf(" ") ;
         }
         print_boxes_color(c,i) ;
      }

   if (col_edges[c-1][i]== '1'){
      printf(cyan"|\n");
   }else if(col_edges[c-1][i]== '2'){
      printf(green"|\n") ;
   }else{
      printf(" \n") ;
      }
   }
}

void print_grid(unsigned short int n){
   short int j ;
   for(j=1 ; j<=n ; j++)
   {
        print_horizontal(j) ;
        print_vertical(j) ;
   }
   print_horizontal(j) ;
}

void free_array(short int row, char **arr) {
    for (short int i = 0; i < row; i++) {
        free(arr[i]);
    }
    free(arr);
}

char small(char c){
   if (c>=65 && c<=90){ return c+32 ; }
   else{return c ;}
}

char big(char c){
   if (c>=97 && c<=122){ return c-32 ; }
   else{return c ;}
}

/*void time_passed(){

   while(win != n*n){
      sleep(1) ;
      game.time++ ;
   }
   
}*/

void check_edges(){   //no errors
   short int i,j ;
   for (i=0 ; i<n ; i++){
      for (j=0 ; j<n ; j++){
         if (row_edges[i][j]!='0' && row_edges[i+1][j]!='0' &&
             col_edges[i][j]!='0' && col_edges[i][j+1] !='0' &&
             boxes[i][j] == '0'){
           
            boxes[i][j] = turn ;
         }
      }
   }
}

short int check_box(short int i,short int j){
   short int n_zeros = 0 ;
   if(boxes[i][j] != '0'){

      if(row_edges[i][j] == '0'){n_zeros++ ; }
      if(row_edges[i][j+1] == '0'){n_zeros++ ; }
      if(col_edges[i][j] == '0'){n_zeros++ ; }
      if(col_edges[i+1][j] == '0'){n_zeros++ ; }

      if(row_edges[i][j] == '0' && n_zeros==1){
         row_edges[i][j] == turn ;
      }
      if(row_edges[i][j+1] == '0' && n_zeros==1){
         row_edges[i][j+1] == turn ;
      }
      if(col_edges[i][j] == '0' && n_zeros==1){
         col_edges[i][j] == turn ;
      }
      if(col_edges[i+1][j] == '0' && n_zeros==1){
         row_edges[i+1][j] == turn ;
      }

      if(n_zeros==1){
         boxes[i][j] == turn ;
         return 1 ;
      }else{
         return 0 ;
      }
   
   }
}

void DFS(short int a,short int b){
   if (check_box(a,b)){

      if(dfs[a-1][b]=='0' && a-1<n && b<n){
         DFS(a-1,b) ;  // go up
         dfs[a-1][b] = '1' ;
      }
      if(dfs[a+1][b]=='0' && a+1<n && b<n){
         DFS(a+1,b) ;  // go down
         dfs[a+1][b] = '1' ;
      }
      if(dfs[a][b-1]=='0' && a<n && b-1<n){
         DFS(a,b-1) ;  // go <--- left
         dfs[a][b-1] = '1' ;
      }
      if(dfs[a][b+1]=='0' && a+1<n && b+1<n){
         DFS(a,b+1) ;  // go ---> right
         dfs[a][b+1] = '1' ;
      }
   
   }
}

void display_stats()
{
    printf("Current turn: %s\n", current_game.turn == 1 ? current_game.player_1.name : current_game.player_2.name);
    printf("Player:\t%s\t%s\n", current_game.player_1.name, current_game.player_2.name);
    printf("Score:\t%d\t%d\t\n", current_game.player_1.score, current_game.player_2.score);
    printf("Moves:\t%d\t%d\t\n", current_game.player_1.number_of_moves, current_game.player_2.number_of_moves);
    printf("Remaining Boxes: %d\n", current_game.number_of_remaining_boxes);
    //we still need to print the time
}

void Winner(player *winner) 
{
    FILE *file = fopen("player_data.txt", "a+");

    if (file == NULL) 
    {
        // create the file if it doesn't exist
        file = fopen("player_data.bin", "w+");
        if (file == NULL) printf("Error opening or creating the file.\n");
    }

    player temp;
    int found = 0;

    //Search for the player in the file

    while (fscanf(file, "%49s %d", temp.name, &temp.score) == 2) 
    {
        if (strcmp(temp.name, winner->name) == 0) 
        {
            found = 1;

            if (winner->score > temp.score) 
            {
                temp.score = winner->score;

                fseek(file, -(49 + sizeof(int) + 2), SEEK_SET);

                fprintf(file, "%s %d\n", temp.name, temp.score);
            }
            break;
        }
    }

    if (!found) 
    {
        fprintf(file, "%s %d\n", winner->name, winner->score);
    }

    fclose(file);
}

void printTopPlayers() 
{
    FILE *file = fopen("player_data.txt", "r");

    if (file == NULL) 
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    player *players = NULL;  // Dynamic array to store players
    int numPlayers = 0;

    // Read players from the file dynamically
    player tempPlayer;
    while (fscanf(file, "%49s %d", tempPlayer.name, &tempPlayer.score) == 2) 
    {
        // Dynamically allocate memory for a new player
        players = realloc(players, (numPlayers + 1) * sizeof(player));

        // Check if memory allocation is successful
        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            exit(1);
        }

        // Copy the temporary player data to the array
        players[numPlayers++] = tempPlayer;
        //numPlayers++;
    }

    fclose(file);

    // Sort the players based on score
    for (int i = 0; i < numPlayers - 1; i++)
    {
        for (int j = i + 1; j < numPlayers; j++) 
        {
            if (players[j].score > players[i].score) 
            {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Top %d Players:\n", numPlayers);

    int numPlayersToPrint = (numPlayers < MAX_PLAYERS_TO_PRINT) ? numPlayers : MAX_PLAYERS_TO_PRINT;

    for (int i = 0; i < numPlayersToPrint; i++) 
    {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }

    // Free dynamically allocated memory
    free(players);
}

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

/*void input_nodes(){
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
}*/

game peek(Stack* stack)
{
    return stack->array[stack->top];
}

game pop(Stack* stack) 
{
    return stack->array[stack->top--];
}

void push(Stack *stack, game game)
{
    stack->array[++stack->top] = game;
}

void empty(Stack *stack) // also used to initialize the stack
{
    stack->top = -1;
}

void empty_both_stacks()
{
    empty(&undo_stack);
    empty(&redo_stack);
}

void undo(Stack *undo_stack,Stack *redo_stack, game *current)
{
    if (current->turn == peek(undo_stack).turn && undo_stack->top != -1)
    {
        push(redo_stack, pop(undo_stack));
        
        printf("Undo successful.\n");
    } 
    else 
    {
        printf("u can't undo anymore.\n");
    }

    *current = peek(undo_stack);
}

void redo(Stack *undo_stack,Stack *redo_stack, game *current)
{
    if (current->turn == peek(redo_stack).turn && undo_stack->top != -1)
    {
        push(undo_stack, pop(redo_stack));
 
        printf("Redo successful.\n");
    } 
    else 
    {
        printf("u can't redo anymore\n");
    }

    *current = peek(undo_stack);
}

int number_of_filled_boxes() 
{
    int count = 0;

    for (int i = 0; i < current_game.size; ++i) 
    {
        for (int j = 0; j < current_game.size; ++j) 
        {
            if (current_game.array_of_boxes[i][j] == '1' || current_game.array_of_boxes[i][j] == '2') 
            {
                count++;
            }
        }
    }

    return count;
}

void switch_turn()
{
    if(number_of_filled_boxes() == current_game.previous_sum)
    {
        printf("entered fn ");
        empty_both_stacks();
        current_game.turn = (current_game.turn == '1') ? '2' : '1';
    }
    current_game.previous_sum = number_of_filled_boxes();
}

void print_menu(){
    
   printf("To Start game [Press S]\n");
   printf("To load previous game [Press L]\n");
   printf("To display Top 10 players [Press T]\n");
   printf("To Exit game [Press E]\n");

   char o;
   scanf(" %c",&o);

   if(small(o) == 'l')
   {
      // function to load from file
   }
   else if(small(o) == 't')
   {
        printTopPlayers();
        print_menu() ;
   }
   else if(small(o) == 'e')
   {
        exit(1) ;
   }
   else
   {
        if(small(o) != 's')
        {
            print_menu();
        }
        else
        {
            input_size();
            current_game.size = n;
            declare_arrays(n);

            printf("Enter [0] to play Vs human\n");
            printf("Enter [1] to play Vs computer\n");

            //function to input mode 
            //current_game.mode = 0;
            
            printf("Enter player 1 name: ");
            scanf("%s", &current_game.player_1.name);
            
            if(current_game.mode == 0)
            {
                printf("Enter player 2 name: ");
                scanf("%s", &current_game.player_2.name);
            }

        }
    }
}

int main()
{
    printf("Welcome to Dots & Boxes game\n");
    while(1)
    {
        print_menu() ;

       // while(number_of_filled_boxes() != n*n)
       // {   
            printf("Player 1 name: %s\n", current_game.player_1.name);
            printf("Player 2 name: %s\n", current_game.player_2.name);

            //flow of the game
       // }
       // print_grid(n) ;
    }
}
