#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 65

typedef struct 
{
    double elapsed_time;
    char turn;
} game;

// Structure to represent the stack
typedef struct 
{
    game array[MAX_SIZE];
    int top; // Index of the top element
} Stack;

Stack undo;
Stack redo;

void initialize(Stack* stack) 
{
    stack->top = -1; // Initialize the top index to -1
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) 
{
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack* stack) 
{
    return stack->top == MAX_SIZE - 1;
}

// Function to get the top element of the stack without removing it
game peek(Stack* stack) // like top() function
{
    game emptyStruct = {0.0, '\0'}; // Return a special value to indicate an error
    if (isEmpty(stack)) 
    {
        printf("The stack is empty. No element to peek.\n");
        return emptyStruct;
    }

    return stack->array[stack->top];
}

game pop(Stack* stack) 
{
    game emptyStruct = {0.0, '\0'}; // Return a special value to indicate an error

    if (isEmpty(stack))
    {
        printf("Stack underflow. Cannot pop from an empty stack.\n");
        return emptyStruct;
    }

    return stack->array[stack->top--];
}

void push_play_to_stack(Stack *stack, game game)
{
    if (isFull(stack)) 
    {
        printf("Stack overflow. Cannot push onto the stack.\n");
        return;
    }

    stack->array[++stack->top] = game;
}

void game_undo(Stack *undo,Stack *redo)
{
    if (!isEmpty(&undo)) 
    {
        push_play_to_stack(&redo, pop(&undo));
        printf("Undo successful.\n");
    } 
    else 
    {
        printf("No moves to undo.\n");
    }
}

void game_redo(Stack *undo,Stack *redo)
{
    if (!isEmpty(&redo)) 
    {
        push_play_to_stack(&undo, pop(&redo));
        printf("Redo successful.\n");
    } 
    else 
    {
        printf("No moves to redo.\n");
    }
}

int main()
{
    initialize(&undo);
    initialize(&redo);

    game first;
    first.elapsed_time = 0.0;
    first.turn = 'A';

    game second;
    second.elapsed_time = 2.0;
    second.turn = 'B';

    game third;
    third.elapsed_time = 3.0;
    third.turn = 'A';

    push_play_to_stack(&undo, first);
    push_play_to_stack(&undo, second);
    push_play_to_stack(&undo, third);


    game current

}