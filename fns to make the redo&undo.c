#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 65

typedef struct 
{
    int id;
    char name[50];
} action;

// Structure to represent the stack
typedef struct 
{
    action array[MAX_SIZE];
    int top; // Index of the top element
} Stack;

// Function to initialize the stack
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

// Function to push an element onto the stack
void push(Stack* stack, action value) 
{
    if (isFull(stack)) 
    {
        printf("Stack overflow. Cannot push onto the stack.\n");
        return;
    }

    stack->array[++stack->top] = value;
}

// Function to pop an element from the stack and it deletes the element
action pop(Stack* stack) 
{
    action emptyStruct = {-1, ""}; // Return a special value to indicate an error

    if (isEmpty(stack))
    {
        printf("Stack underflow. Cannot pop from an empty stack.\n");
        return emptyStruct;
    }

    return stack->array[stack->top--];
}

// Function to get the top element of the stack without removing it
action peek(Stack* stack) // like top() function
{
    action emptyStruct = {-1, ""}; // Return a special value to indicate an error
    if (isEmpty(stack)) 
    {
        printf("The stack is empty. No element to peek.\n");
        return emptyStruct;
    }

    return stack->array[stack->top];
}

// Example usage
int main() 
{
    Stack myStack;
    initialize(&myStack);

    // Push some elements onto the stack
    for (int i = 1; i <= 5; ++i) {
        action element = {i, "Name"};
        push(&myStack, element);
    }

    // Pop and print elements
    while (!isEmpty(&myStack)) {
        action poppedElement = pop(&myStack);
        printf("Popped element: id=%d, name=%s\n", poppedElement.id, poppedElement.name);
    }

    return 0;
}
