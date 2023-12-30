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
    short int index_flag;
    unsigned short int size;
    char array_of_row_edges[MAX_GRID_SIZE+1][MAX_GRID_SIZE];
    char array_of_column_edges[MAX_GRID_SIZE][MAX_GRID_SIZE+1];
    char array_of_boxes[MAX_GRID_SIZE][MAX_GRID_SIZE];
    unsigned int elapsed_time;
    char turn;
    int number_of_remaining_boxes;
    player player_1;
    player player_2;
    int previous_sum;
    unsigned short int mode; // 1 --> computer
} game;

game current_game;

typedef struct 
{
    game array[MAX_SIZE_OF_STACK];
    int pointer_to_index;
} Stack;

Stack Game_stack;

FILE* file;

int UndoRedoFlag;

void empty_stack();

void reset_variables_to_zeros()
{
    current_game.turn = '1';
    current_game.player_1.number_of_moves = 0;
    current_game.player_2.number_of_moves = 0;
    current_game.player_1.score = 0;
    current_game.player_2.score = 0;
    empty_stack();
    current_game.index_flag = 1;
    current_game.elapsed_time = 0;
}

void clearInputBuffer() 
{
    int c;

    while ((c = getchar()) != '\n' && c != EOF) 
    {
        // Keep reading characters until newline or end of file
    }
}

void print_horizontal(short int r)
{
   short int i ;   ///r is not index , if r=2 ---> row that has index 1
   for(i=0 ; i < current_game.size ; i++){
        printf(white"+"RESET) ;
        
        if (current_game.array_of_row_edges[r-1][i] == '1'){
            printf(cyan"%s"RESET,line) ;
        }else if(current_game.array_of_row_edges[r-1][i] == '2'){
            printf(green"%s"RESET,line) ;
        }else{
            printf("       ") ;
        }
   }
   printf(white"+\n"RESET) ;
}

void print_boxes_color(short int c,short int i)
{
    if (current_game.array_of_boxes[c-1][i] == '1')
    {
        printf(back_cyan"       "RESET);
    }
    else if(current_game.array_of_boxes[c-1][i] == '2')
    {
        printf(back_green"       "RESET);
    }
    else
    {
        printf("       ");
    }
}

void print_vertical(short int c)
{
   int i ;
   for(int j=0; j<3 ;j++){
      for(i=0 ; i<current_game.size ; i++){

         if(current_game.array_of_column_edges[c-1][i] =='1' || current_game.array_of_boxes[c-1][i] == '1'){
            printf(cyan"|"RESET) ;
         }else if(current_game.array_of_column_edges[c-1][i] =='2' || current_game.array_of_boxes[c-1][i] == '2'){
            printf(green"|"RESET) ;
         }else{
            printf(" ") ;
         }
         print_boxes_color(c,i) ;
      }

   if (current_game.array_of_column_edges[c-1][i]== '1'){
      printf(cyan"|\n"RESET);
   }else if(current_game.array_of_column_edges[c-1][i]== '2'){
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

    for(j = 1 ; j <= current_game.size ; j++)
    {
        print_horizontal(j);
        print_vertical(j);
    }

    print_horizontal(j);

    printf("\n");
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

    for (i=0 ; i<current_game.size ; i++)
    {
        for (j=0 ; j<current_game.size ; j++)
        {
            if (current_game.array_of_row_edges[i][j]!='\0' && current_game.array_of_row_edges[i+1][j]!='\0' &&
                current_game.array_of_column_edges[i][j]!='\0' && current_game.array_of_column_edges[i][j+1] !='\0' &&
                current_game.array_of_boxes[i][j] == '\0')
            {
                current_game.array_of_boxes[i][j] = current_game.turn ;
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
            if (current_game.array_of_boxes[i][j] != '\0')
            {
                count++;
            }
        }
    }
    return count;
}

void display_stats()
{
    printf("\nNext turn: %s\n", current_game.turn == '1' ? current_game.player_1.name : current_game.player_2.name);
    printf("Player:\t%s\t%s\n", current_game.player_1.name, current_game.player_2.name);
    printf("Score:\t%d\t%d\t\n", current_game.player_1.score, current_game.player_2.score);
    printf("Moves:\t%d\t%d\t\n", current_game.player_1.number_of_moves, current_game.player_2.number_of_moves);
    printf("Remaining Boxes: %d\n", current_game.number_of_remaining_boxes);
    //we still need to print the time
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
            current_game.size = arr[1] + (arr[0]*10) ;
        }
        else
        {
            current_game.size = arr[0] ;
        }
    }
    else
    {
        printf("Invalid input\n");
        clearInputBuffer();
        input_size() ;
    }
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

void print_options();
void empty_redo_stack();

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

    if(r1>current_game.size+1 || r2>current_game.size+1 || c1>current_game.size+1 || c2>current_game.size+1)
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
        if(current_game.array_of_row_edges[r1-1][min(c1,c2)-1]!='\0')
        {
            printf("Invalid input\n") ;
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(c1==c2)
    {
        if(current_game.array_of_column_edges[min(r1,r2)-1][c1-1]!='\0')
        {          
            printf("Invalid input\n");
            clearInputBuffer();
            input_nodes() ;
            return;
        }
    }

    if(r1==r2)
    {
        current_game.array_of_row_edges[r1-1][min(c1,c2)-1] = current_game.turn ;
        check_edges();
        empty_redo_stack();
        UndoRedoFlag = 0;
    }
    else
    { //c1==c2
        current_game.array_of_column_edges[min(r1,r2)-1][c1-1] = current_game.turn ;
        check_edges();
        empty_redo_stack();
        UndoRedoFlag = 0;
    }
    
}

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

// Function to serialize and save the game to a binary file
int saveGame(game* gamePtr) 
{
    /*for (int i = 0; i <= current_game.size; ++i) 
    {
        for (int j = 0; j < current_game.size; ++j) 
        {
            gamePtr->array_of_row_edges[i][j] = current_game.array_of_row_edges[i][j];
        }
    }

    // Copy col_edges to array_of_column_edges
    for (int i = 0; i < current_game.size; ++i) 
    {
        for (int j = 0; j <= current_game.size; ++j) 
        {
            gamePtr->array_of_column_edges[i][j] = col_edges[i][j];
        }
    }

    // Copy boxes to array_of_boxes
    for (int i = 0; i < current_game.size; ++i) 
    {
        for (int j = 0; j < current_game.size; ++j) 
        {
            gamePtr->array_of_boxes[i][j] = boxes[i][j];
        }
    }*/

    file = fopen("saved_game.bin", "wb");
    if (file != NULL) 
    {
        // Serialize the game struct
        fwrite(gamePtr, sizeof(game), 1, file);
        fclose(file);
        printf("Game saved successfully.\n");
        return 1;
    } 
    else 
    {
        fprintf(stderr, "Unable to open file for saving.\n");
        return 0;
    }
}
//saveGame(&myGame, "saved_game.bin")

// Function to deserialize and load the game from a binary file
void loadGame(game* gamePtr) 
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
        printf("Game loaded successfully.\n");
    } 
    else 
    {
        fprintf(stderr, "Unable to open file for loading.\n");
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

void undo();
void redo();

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
        undo();
        UndoRedoFlag = 1;
        print_grid();
        display_stats();
        return;
    }
    else if(op == 'r')
    {
        redo();
        UndoRedoFlag = 1;
        print_grid();
        display_stats();
        return;
    }
    else if(op =='s')
    {
        saveGame(&current_game);
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
            loadGame(&current_game);
            //declare_arrays();
            //copy_game_arrays_to_Ahmed();
            empty_stack();
            return;
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

                //declare_arrays();

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

/*void time_passed()
{
    while(1)
    {
        Sleep(1000) ;
        current_game.elapsed_time++;
    }
}*/

void push()
{
    //current_game.index_flag = 1;
    Game_stack.array[++Game_stack.pointer_to_index] = current_game;
}

void undo()
{
    if (Game_stack.pointer_to_index > 0)
    {
        Game_stack.pointer_to_index--;
        current_game = Game_stack.array[Game_stack.pointer_to_index];

        //copy_game_arrays_to_Ahmed();

        printf("\n\nUndo successful.\n\n");
    } 
    else 
    {
        printf("\n\nu can't undo anymore.\n\n");
    }
}

void redo()
{
    if (Game_stack.array[Game_stack.pointer_to_index + 1].index_flag > 0)
    {
        Game_stack.pointer_to_index++;

        current_game = Game_stack.array[Game_stack.pointer_to_index];

        //copy_game_arrays_to_Ahmed();

        printf("\n\nRedo successful.\n\n");
    } 
    else 
    {
        printf("\n\nu can't redo anymore\n\n");
    }
}

void empty_redo_stack()
{
    for(int i = Game_stack.pointer_to_index + 1 ; i < MAX_SIZE_OF_STACK ; i++)
    {
        if(Game_stack.array[i].index_flag == 0)
        {
            break;
        }
        else
        {
            Game_stack.array[i].index_flag = 0;
        }
    }
}

void empty_stack()
{
    for(int i = 0 ; i < MAX_SIZE_OF_STACK ; i++)
    {
        if(Game_stack.array[i].index_flag == 0)
        {
            break;
        }
        else
        {
            Game_stack.array[i].index_flag = 0;
        }
    }

    Game_stack.pointer_to_index = -1;
}

void switch_turn()
{
    int temp = number_of_filled_boxes();

    if (current_game.turn == '1') 
    {
        current_game.player_1.number_of_moves++;
    } 
    else 
    {
        current_game.player_2.number_of_moves++;
    }

    if(temp == current_game.previous_sum)
    {
        empty_stack();   
        current_game.turn = (current_game.turn == '1') ? '2' : '1';
    }
    else
    {
        if (current_game.turn == '1') 
        {
            current_game.player_1.score += temp - current_game.previous_sum;
        } 
        else 
        {
            current_game.player_2.score += temp - current_game.previous_sum;
        }
        // push only if he closes a box
        push();
    }
    current_game.number_of_remaining_boxes = (current_game.size * current_game.size) - temp;
}

int main()
{
    printf("Welcome to Dots & Boxes game\n");

    while(1)
    {
        print_menu();

        //pthread_t time_thread ;
        //pthread_create(&time_thread, NULL, time_passed, NULL) ;

        print_grid();
        display_stats();

        while(number_of_filled_boxes() != current_game.size*current_game.size)
        {
            current_game.previous_sum = number_of_filled_boxes();
            clearInputBuffer();
            input_nodes();

            if(UndoRedoFlag != 1)
            {
                print_grid();
                switch_turn();
                display_stats();
            }
        }
        player winnerName = (current_game.player_1.score > current_game.player_2.score)
        ? current_game.player_1
        : current_game.player_2;
        Winner(&winnerName);
        printTopPlayers();
    }
}