#include <stdio.h>
#include <time.h>

double get_time()
{
    return (double)clock() / CLOCKS_PER_SEC;
}
/*clock_t clock(void) returns the number of clock ticks elapsed since the program was launched.
To get the number of seconds used by the CPU, you will need to divide by CLOCKS_PER_SEC.*/

int main() 
{
    double start_time = get_time();

    double temp = start_time;

    double elapsed_time = 0;

    while (1) 
    {
        double current_time = get_time();

        elapsed_time = current_time - start_time;

        //printf("Time elapsed: %.2d:%.2d \n", (int)elapsed_time / 60, (int)elapsed_time % 60);

        if ((current_time - temp) > 60.0)
        {
            temp += 60.0;
            printf("Player has been idle for 1 minute.\n");
        }
    }
}