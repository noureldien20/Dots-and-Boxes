#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
//#include <pthread.h>

#define MAX_SIZE_OF_STACK 15
#define MAX_PLAYERS_TO_PRINT 10
#define MAX_NAME_LENGHT 40
#define MAX_GRID_SIZE 10

#define green "\x1b[0;92m"
#define yellow "\x1b[0;93m"
#define cyan "\x1b[96m"
#define white "\x1b[97m"
#define back_cyan "\x1b[106m"
#define back_green "\x1b[102m"
#define back_white "\x1b[107m"
#define RESET "\x1b[0m"
#define line "-------"

typedef struct 
{
   char name[MAX_NAME_LENGHT + 1];
   int score;
   int number_of_moves;
} player;

typedef struct 
{
    unsigned short int size;
    char array_of_row_edges[MAX_GRID_SIZE+1][MAX_GRID_SIZE];
    char array_of_column_edges[MAX_GRID_SIZE][MAX_GRID_SIZE+1];
    char array_of_boxes[MAX_GRID_SIZE][MAX_GRID_SIZE];
    unsigned int elapsed_time;
    char turn;
    player player_1;
    player player_2;
    unsigned short int mode; // 1 --> computer
} game;

game current_game;

typedef struct 
{
    char array_of_row_edges[MAX_GRID_SIZE+1][MAX_GRID_SIZE];
    char array_of_column_edges[MAX_GRID_SIZE][MAX_GRID_SIZE+1];
    char array_of_boxes[MAX_GRID_SIZE][MAX_GRID_SIZE];
} GameArrays;

GameArrays current_game_arrays;

typedef struct 
{
    GameArrays array[MAX_SIZE_OF_STACK];
    int top;
} Stack;

Stack undo_stack;
Stack redo_stack;

FILE* file;

unsigned short int n ;
char **row_edges ;
char **col_edges ;
char **boxes ;
char **dfs ;
short int indexes[3] = {0,0,0}; 
int undo_flag;
int previous_sum;

int number_of_filled_boxes();
void generate_edges();
void inputGameMode();
//void time_passed();
void inputGameMode();
void printTopPlayers();
player* loadPlayers(int* numPlayers);
void Winner(player* winner);
void clearInputBuffer();
char **create_array(short int row, short int col);
void declare_arrays();
void zero_2D_array(short int row, short int col, char **arr);
void print_array_2D(short int row, short int col, char **arr);
void print_horizontal(short int r);
void print_boxes_color(short int c, short int i);
void print_vertical(short int c);
void print_grid();
void free_array(short int row, char **arr);
char small(char c);
char big(char c);
void check_edges();
GameArrays peek(Stack* stack);
GameArrays pop(Stack* stack);
void push(Stack *stack, GameArrays current_game_arrays);
void empty(Stack *stack);
void empty_both_stacks();
int min(int a, int b);
unsigned short int check_node(char x);
void copy_stack_arrays_to_Ahmed();
void copy_game_arrays_to_Ahmed();
void copy_stack_arrays_from_Ahmed();
void copy_game_arrays_from_Ahmed();
void reset_variables_to_zeros();
void display_stats();
void input_size();
void undo(Stack* undo_stack, Stack* redo_stack, GameArrays* current);
void redo(Stack* undo_stack, Stack* redo_stack, GameArrays* current);
void switch_turn();
void input_nodes();
int saveGame(game* gamePtr);
int loadGame(game* gamePtr);
void print_options();
void print_menu();
void update_stats();

int main()
{
    printf("Welcome to Dots & Boxes game\n");

    while(1)
    {
        print_menu();

        //pthread_t time_thread ;
        //pthread_create(&time_thread, NULL, time_passed, NULL) ;

        print_grid();
        update_stats();
        display_stats();

        while(number_of_filled_boxes() != n*n)
        {
            previous_sum = number_of_filled_boxes();
            clearInputBuffer();
            input_nodes();
            check_edges();
            if(undo_flag == 0)
            {
                switch_turn();
            }
            print_grid();
            display_stats();
        }
        player winnerName = (current_game.player_1.score > current_game.player_2.score)
        ? current_game.player_1
        : current_game.player_2;
        Winner(&winnerName);
        printTopPlayers();
    }
}

void generate_edges() 
{
    for(int i = 0 ; i < n ; i++)
    {
        for(int j = 0 ; j < n  ; j++)
        {
            if(dfs[i][j] == '1')
            {
                row_edges[i][j] = current_game.turn;
                row_edges[i + 1][j] = current_game.turn;
                col_edges[i][j] = current_game.turn;
                col_edges[i][j + 1] = current_game.turn;
                boxes[i][j] == current_game.turn ;
            }
        }
    }
}

/*void time_passed()
{
    while(1)
    {
        Sleep(1000) ;
        current_game.elapsed_time++;
    }
}*/

void inputGameMode() 
{
    char temp[3];

    printf("Enter game mode [0 for human vs human, 1 for human vs computer] : ");

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

// Display the top players and their scores
void printTopPlayers() 
{
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    // Sort the players based on score
    for(int i = 0; i < numPlayers - 1; i++) 
    {
        for(int j = i + 1; j < numPlayers; j++) 
        {
            if(players[j].score > players[i].score) 
            {
                player temp = players[i];
                players[i] = players[j];
                players[j] = temp;
            }
        }
    }

    printf("Top %d Players:\n", numPlayers);

    int numPlayersToPrint = (numPlayers < MAX_PLAYERS_TO_PRINT) ? numPlayers : MAX_PLAYERS_TO_PRINT;

    for(int i = 0; i < numPlayersToPrint; i++)
    {
        printf("%d. %s - %d\n", i + 1, players[i].name, players[i].score);
    }

    // Free dynamically allocated memory
    free(players);
}

//The loadPlayers function deserializes and loads all players from the binary file. It returns a dynamic array of
//Player structs and updates the numPlayers variable.
//The Winner function uses loadPlayers to get the existing players, updates the information for the winner,
//and then saves the updated players back to the file.
//The printTopPlayers function also uses loadPlayers to get the players and then sorts and prints the top players based on their scores.

// Deserialize and load players from a binary file
player* loadPlayers(int* numPlayers) 
{
    FILE* file = fopen("player_data.bin", "rb");

    if (file == NULL) 
    {
        printf("File not found. Creating a new file.\n");

        // Create a new file if it doesn't exist
        file = fopen("player_data.bin", "wb");
        
        if (file == NULL) 
        {
            printf("Error creating the file.\n");
            return NULL;
        }

        fclose(file);

        // Now attempt to open the file again
        file = fopen("player_data.bin", "rb");

        if (file == NULL) 
        {
            printf("Error opening the file.\n");
            return NULL;
        }
    }

    player* players = NULL;
    *numPlayers = 0;

    player tempPlayer;

    while (fread(&tempPlayer, sizeof(player), 1, file) == 1) 
    {
        players = realloc(players, (*numPlayers + 1) * sizeof(player));

        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            fclose(file);
            return NULL;
        }

        players[(*numPlayers)++] = tempPlayer;
    }

    fclose(file);

    return players;
}

void Winner(player* winner) 
{
    player* players;
    int numPlayers;

    // Load existing players from the file
    players = loadPlayers(&numPlayers);

    int found = 0;

    // Search for the player in the array
    for (int i = 0; i < numPlayers; i++) 
    {
        if (strcmp(players[i].name, winner->name) == 0) 
        {
            found = 1;

            if (winner->score > players[i].score) 
            {
                players[i].score = winner->score;
            }
            break;
        }
    }

    if (!found) 
    {
        // Add the winner to the array
        players = realloc(players, (numPlayers + 1) * sizeof(player));

        if (players == NULL) 
        {
            printf("Memory allocation failed.\n");
            return;
        }

        players[numPlayers++] = *winner;
    }

    // Save the updated players to the file
    FILE* file = fopen("player_data.bin", "wb");
    if (file != NULL) 
    {
        fwrite(players, sizeof(player), numPlayers, file);
        fclose(file);
    } 
    else 
    {
        printf("Error opening the file for saving.\n");
    }

    // Free dynamically allocated memory
    free(players);
}

void clearInputBuffer() 
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) 
    {
        // Keep reading characters until newline or end of file
    }
}

char **create_array(short int row,short int col){
   char **arr = (char **)calloc(row, sizeof(char *)) ;
   
   for(short int i=0 ; i<row ; i++){
      arr[i] = (char *)calloc(col, sizeof(char));
   }
   return arr ;
}

void declare_arrays(){
   row_edges = create_array(n+1,n) ;
   col_edges = create_array(n,n+1) ;
   boxes = create_array(n,n) ;
   dfs = create_array(n,n) ;
}

void zero_2D_array(short int row,short int col,char **arr){

   for (int i=0 ; i<row ; i++)
   {
        for (int j=0 ; j<col ; j++)
        {
            arr[i][j] = '\0' ; 
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
        printf(white"+"RESET) ;
        
        if (row_edges[r-1][i] == '1'){
            printf(cyan"%s"RESET,line) ;
        }else if(row_edges[r-1][i] == '2'){
            printf(green"%s"RESET,line) ;
        }else{
            printf("       ") ;
        }
   }
   printf(white"+\n"RESET) ;
}

void print_boxes_color(short int c,short int i)
{
    if (boxes[c-1][i] == '1')
    {
        printf(back_cyan"       "RESET);
    }
    else if(boxes[c-1][i] == '2')
    {
        printf(back_green"       "RESET);
    }
    else
    {
        printf("       ");
    }
}

void print_vertical(short int c){
   int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<n ; i++){

         if(col_edges[c-1][i] =='1' || boxes[c-1][i] == '1'){
            printf(cyan"|"RESET) ;
         }else if(col_edges[c-1][i] =='2' || boxes[c-1][i] == '2'){
            printf(green"|"RESET) ;
         }else{
            printf(" ") ;
         }
         print_boxes_color(c,i) ;
      }

   if (col_edges[c-1][i]== '1'){
      printf(cyan"|\n"RESET);
   }else if(col_edges[c-1][i]== '2'){
      printf(green"|\n"RESET) ;
   }else{
      printf(" \n") ;
      }
   }
}

void print_grid()
{
    printf("\n");

    short int j ;

    for(j = 1 ; j <= n ; j++)
    {
        print_horizontal(j);
        print_vertical(j);
    }

    print_horizontal(j);

    printf("\n");
}

void free_array(short int row, char **arr) 
{
    for(short int i = 0; i < row; i++) 
    {
        free(arr[i]);
    }
    free(arr);
}

char small(char c)
{
    if(c>=65 && c<=90)
    { 
        return c+32;
    }
    else
    {
        return c ;
    }
}

char big(char c)
{
    if (c >= 97 && c <= 122)
    { 
        return c-32 ; 
    }
    else
    {
        return c ;
    }
}

void check_edges()
{
    short int i,j ;

    for (i=0 ; i<n ; i++)
    {
        for (j=0 ; j<n ; j++)
        {
            if (row_edges[i][j]!='\0' && row_edges[i+1][j]!='\0' &&
                col_edges[i][j]!='\0' && col_edges[i][j+1] !='\0' &&
                boxes[i][j] == '\0')
            {
                boxes[i][j] = current_game.turn ;
            }
        }
    }
}

int number_of_filled_boxes() 
{
    int count = 0;

    for (int i = 0; i < current_game.size; ++i) 
    {
        for (int j = 0; j < current_game.size; ++j) 
        {
            if (boxes[i][j] != '\0')
            {
                count++;
            }
        }
    }
    return count;
}

GameArrays peek(Stack* stack)
{
    return stack->array[stack->top];
}

GameArrays pop(Stack* stack) 
{
    return stack->array[stack->top--];
}

void push(Stack *stack, GameArrays current)
{
    stack->array[++stack->top] = current;
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

int min(int a, int b)
{
    return (a < b) ? a : b;
}

unsigned short int check_node(char x)
{
   if ((int)x <= 57 && (int)x >= 49){ // integer
         return 1;
       }else{
         return 0 ;
      }
}

void copy_stack_arrays_to_Ahmed() 
{
    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            row_edges[i][j] = current_game_arrays.array_of_row_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            col_edges[i][j] = current_game_arrays.array_of_column_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            boxes[i][j] = current_game_arrays.array_of_boxes[i][j];
        }
    }
}

void copy_game_arrays_to_Ahmed()
{
    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            row_edges[i][j] = current_game.array_of_row_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            col_edges[i][j] = current_game.array_of_column_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            boxes[i][j] = current_game.array_of_boxes[i][j];
        }
    }
}

void copy_stack_arrays_from_Ahmed()
{
    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            current_game_arrays.array_of_row_edges[i][j] = row_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            current_game_arrays.array_of_column_edges[i][j] = col_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            current_game_arrays.array_of_boxes[i][j] = boxes[i][j];
        }
    }
}

void copy_game_arrays_from_Ahmed()
{
    for (int i = 0; i <= n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            current_game.array_of_row_edges[i][j] = row_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j <= n; ++j) 
        {
            current_game.array_of_column_edges[i][j] = col_edges[i][j];
        }
    }

    for (int i = 0; i < n; ++i) 
    {
        for (int j = 0; j < n; ++j) 
        {
            current_game.array_of_boxes[i][j] = boxes[i][j];
        }
    }
}

void reset_variables_to_zeros()
{
    current_game.turn = '1';
    empty_both_stacks();
    current_game.elapsed_time = 0;
    undo_flag = 0;
}

void display_stats()
{
    update_stats();
    
    printf("Next turn: %s\n", current_game.turn == '1' ? current_game.player_1.name : current_game.player_2.name);
    printf("Player:\t%s\t%s\n", current_game.player_1.name, current_game.player_2.name);
    printf("Score:\t%d\t%d\t\n", current_game.player_1.score, current_game.player_2.score);
    printf("Moves:\t%d\t%d\t\n", current_game.player_1.number_of_moves, current_game.player_2.number_of_moves);
    printf("Remaining Boxes: %d\n", current_game.size * current_game.size - number_of_filled_boxes());
    printf("Time: %d:%d\n", current_game.elapsed_time / 60, current_game.elapsed_time % 60 );
}

void input_size()
{
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
    )
    {
        arr[0] = (unsigned short int)temp[0] - 48 ;

        if (temp[1]!='\0')
        {
            arr[1] = (unsigned short int)temp[1] - 48 ;
            n = arr[1] + (arr[0]*10) ;
        }
        else
        {
            n = arr[0] ;
        }
    }
    else
    {
        printf("Invalid input\n");
        clearInputBuffer();
        input_size() ;
    }
}

void undo(Stack *undo_stack,Stack *redo_stack, GameArrays *current)
{
    if (undo_stack->top  > 0)
    {
        push(redo_stack, pop(undo_stack));
        
        printf("\nUndo successful.\n\n");

        *current = peek(undo_stack);
        copy_stack_arrays_to_Ahmed();
        undo_flag = 1;
    } 
    else 
    {
        printf("\nu can't undo anymore.\n\n");
        undo_flag = 1;
    }
}

void redo(Stack *undo_stack,Stack *redo_stack, GameArrays *current)
{
    if (undo_stack->top > 0)
    {
        push(undo_stack, pop(redo_stack));
 
        printf("\nRedo successful.\n\n");

        *current = peek(undo_stack);
        copy_stack_arrays_to_Ahmed();
        undo_flag = 1;
    } 
    else 
    {
        printf("\nu can't redo anymore\n\n");
        undo_flag = 1;
    }
}

void switch_turn()
{
    int temp = number_of_filled_boxes();

    if(temp == previous_sum)
    {
        empty_both_stacks();
        current_game.turn = (current_game.turn == '1') ? '2' : '1';
    }
    else
    {
        copy_stack_arrays_from_Ahmed();
        push(&undo_stack, current_game_arrays);
    }
}

void input_nodes()
{ //bta3t ahmed
    unsigned short int r1,r2,c1,c2;
    printf("Enter 2 dots (row,row,col,col), for options [Press o]: ");

    char temp[10] = {'\0'};
    scanf("%4s",temp);

    if(temp[0] == 'o' || temp[0] == 'O')
    {
        clearInputBuffer();
        print_options();
        return;
    }

    if(!(check_node(temp[0]) && check_node(temp[1]) && check_node(temp[2]) && check_node(temp[3])))
    {
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    r1 = (unsigned short int)temp[0] - 48 ;
    r2 = (unsigned short int)temp[1] - 48 ;
    c1 = (unsigned short int)temp[2] - 48 ;
    c2 = (unsigned short int)temp[3] - 48 ;

    if(r1>n+1 || r2>n+1 || c1>n+1 || c2>n+1)
    {
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    if(
        !(r1==r2 || c1==c2) ||   //nodes are adjacent
        !(abs(r1-r2)==1 || abs(c1-c2)==1) //short line not long line
        )
    {
        printf("Invalid input\n") ;
        clearInputBuffer();
        input_nodes() ;
        return;
    }

    if(r1==r2)
    {
        if(row_edges[r1-1][min(c1,c2)-1]!='\0')
        {
            printf("Invalid input\n") ;
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(c1==c2)
    {
        if(col_edges[min(r1,r2)-1][c1-1]!='\0')
        {          
            printf("Invalid input\n");
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(r1==r2)
    {
        row_edges[r1-1][min(c1,c2)-1] = current_game.turn ;
        indexes[0] = r1-1 ;
        indexes[1] = min(c1,c2)-1 ;
        indexes[3] = 0 ;
        undo_flag = 0;
        empty(&redo_stack);
    }
    else
    { //c1==c2
        col_edges[min(r1,r2)-1][c1-1] = current_game.turn ;
        indexes[0] = min(r1,r2)-1 ;
        indexes[1] = c1-1 ;
        indexes[3] = 1 ;
        undo_flag = 0;
        empty(&redo_stack);
    }
}

// Function to serialize and save the game to a binary file
int saveGame(game* gamePtr) 
{
    copy_game_arrays_from_Ahmed();

    file = fopen("saved_game.bin", "wb");
    if (file != NULL) 
    {
        // Serialize the game struct
        fwrite(gamePtr, sizeof(game), 1, file);
        fclose(file);
        printf("\nGame saved successfully.\n\n");
        return 1;
    } 
    else 
    {
        printf("\nUnable to open file for saving.\n\n");
        return 0;
    }
}

// Function to deserialize and load the game from a binary file
int loadGame(game* gamePtr) 
{
    file = fopen("saved_game.bin", "rb");
    if (file != NULL) 
    {
        // Get the size of the file
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        // Deserialize the game struct
        char* buffer = (char*)malloc(fileSize);
        fread(buffer, fileSize, 1, file);
        memcpy(gamePtr, buffer, sizeof(game));
        free(buffer);

        fclose(file);
        printf("\nGame loaded successfully.\n\n");
        return 1;
    } 
    else 
    {
        printf("\nUnable to open file for loading.\n\n");
        return 0;
    }
}

void print_options()
{
    printf("To Make a move [Press M]\n");
    printf("To Undo [Press U]\n");
    printf("To Redo [Press R]\n");
    printf("To Save game [Press S]\n");
    printf("To Exit game [Press E]\n");
    printf("Option: ");

    char temp[5] ;
    char op ;
    scanf("%1s",temp) ;

    if(temp[1]!='\0')
    {
        printf("Invalid input\n");
        clearInputBuffer();
        print_options();
        return;
    }else
    {
        op = small(temp[0]);
    }
    
    if(op == 'u')
    {
        undo(&undo_stack, &redo_stack, &current_game_arrays);
        clearInputBuffer();
        return;
    }
    else if(op == 'r')
    {
        redo(&undo_stack, &redo_stack, &current_game_arrays);
        clearInputBuffer();
        return;
    }
    else if(op =='s')
    {
        saveGame(&current_game);
        undo_flag = 1;
        return;
    }
    else if(op =='e')
    {
        exit(1);
    }
    else if(op =='m')
    {
        clearInputBuffer();
        input_nodes();
        return;
    }
    else
    {
        printf("Invalid input\n");
        clearInputBuffer();
        print_options();
        return;
    }
}

void print_menu()
{
    printf("\nTo Start game [Press S]\n");
    printf("To load previous game [Press L]\n");
    printf("To display Top 10 players [Press T]\n");
    printf("To Exit game [Press E]\n");
    printf("Option: ");

    char temp[5] ;
    char op ;
    scanf("%1s",temp);

        if(temp[1]!='\0')
        {
            printf("Invalid input\n");
            clearInputBuffer();
            print_menu() ;
            return;
        }
        else
        {
            op = small(temp[0]) ;
        }

        if(op == 'l')
        {
            if(loadGame(&current_game))
            {
                n = current_game.size;
                undo_flag = 0;
                declare_arrays();
                copy_game_arrays_to_Ahmed();
                empty_both_stacks();
                return;
            }
            else
            {
                print_menu();
                return;
            }
        }
        else if(op == 't')
        {
            printTopPlayers();
            clearInputBuffer();
            print_menu();
            return;
        }
        else if(op == 'e')
        {
            exit(1);
        }
        else
        {
            if(op !='s')
            {
                clearInputBuffer();
                print_menu();
                return;
            }
            else
            {
                clearInputBuffer();
                input_size();
                current_game.size = n;

                declare_arrays();

                clearInputBuffer();

                inputGameMode();
                
                printf("Enter player 1 name: ");
                clearInputBuffer();
                scanf("%40s", &current_game.player_1.name);
                
                if(current_game.mode == 0)
                {
                    printf("Enter player 2 name: ");
                    clearInputBuffer();
                    scanf("%40s", &current_game.player_2.name);
                }
                else
                {
                    strcpy(current_game.player_2.name , "computer");
                }

                reset_variables_to_zeros();
            }
        }
}

void update_stats()
{
    current_game.player_1.number_of_moves = 0;
    current_game.player_2.number_of_moves = 0;
    current_game.player_1.score = 0;
    current_game.player_2.score = 0;

    for (int i = 0; i < n + 1; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if(row_edges[i][j] == '1') 
            {
                (current_game.player_1.number_of_moves)++;
            } 
            else if (row_edges[i][j] == '2') 
            {
                (current_game.player_2.number_of_moves)++;
            }
        }
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n + 1; j++) 
        {
            if(col_edges[i][j] == '1') 
            {
                (current_game.player_1.number_of_moves)++;
            } 
            else if(col_edges[i][j] == '2') 
            {
                (current_game.player_2.number_of_moves)++;
            }
        }
    }

    for (int i = 0; i < n; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            if(boxes[i][j] == '1') 
            {
                (current_game.player_1.score)++;
            } 
            else if (row_edges[i][j] == '2') 
            {
                (current_game.player_2.score)++;
            }
        }
    }

}