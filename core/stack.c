#include "stack.h"

void Initialize(Stack *stack)
{
    stack->top = 0;
}

int IsEmpty(Stack *stack)
{
    if(stack->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int IsFull(Stack *stack)
{
    if(stack->top == MAX_STACK_SIZE)
    {
        return 1;
    }
    else {
        return 0;
    }
}

void Push(Stack *stack, int x)
{
    stack->data[stack->top] = x;
    stack->top++;
}

int Pop(Stack *stack)
{
    int x;
    stack->top--;
    x = stack->data[stack->top];
    return x;
}

int GetTop(Stack *stack)
{
    return (stack->data[stack->top - 1]);
}