






void free_array(short int row, char **arr) 
{
    for(short int i = 0; i < row; i++) 
    {
        free(arr[i]);
    }
    free(arr);
}

// Deserialize and load players from a binary file


int main()
{
    printf("Welcome to Dots & Boxes game\n");

    while(1)
    {
        print_menu();

        pthread_t time_thread ;
        pthread_create(&time_thread, NULL, time_passed, NULL) ;

        print_grid();

        while(number_of_filled_boxes() != n*n)
        {
            current_game.previous_sum = number_of_filled_boxes();
            clearInputBuffer();
            input_nodes();
            check_edges();
            print_grid();
            switch_turn();
            display_stats();
        }
        player winnerName = (current_game.player_1.score > current_game.player_2.score)
        ? current_game.player_1
        : current_game.player_2;
        Winner(&winnerName);
        printTopPlayers();
    }
}
