#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

void InitializeStack(Stack *stack)
{
    stack->top = 0;
}

int IsStackEmpty(Stack *stk)
{
    if(stk->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void PushStack(Stack *stk, Token *tk)
{
    if (stk->top < MAX_STACK_SIZE)
    {
        stk->data[stk->top] = *tk;
        stk->top++;
    }
    else
    {
        printf("Stack overflow error, total amount of elements is: %d !\n", stk->top);
        exit(-6);
    }
}

Token PopStack(Stack *stk)
{
    Token pelem;
    if(stk->top > 0)
    {
        stk->top--;
        pelem = stk->data[stk->top];
        return pelem;
    }
    else
    {
        printf("Stack is empty!\n");
        exit(-5);
        return pelem; // todo exit
    }
}

Token GetStackTop(Stack *stk)
{
    if(stk->top > 0)
    {
        return stk->data[stk->top - 1];
    }
    else
    {
        printf("Stack is empty!\n");
    }
}


void InitializeComplexStack(ComplexStack *stack)
{
    stack->top = 0;
}

int IsComplexStackEmpty(ComplexStack *stk)
{
    if(stk->top == 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void PushComplexStack(ComplexStack *stk, Complex *tk)
{
    if (stk->top < MAX_STACK_SIZE)
    {
        stk->data[stk->top] = *tk;
        stk->top++;
    }
    else
    {
        printf("Stack overflow error, total amount of elements is: %d !\n", stk->top);
        exit(-6);
    }
}

Complex PopComplexStack(ComplexStack *stk)
{
    Complex pelem;
    if(stk->top > 0)
    {
        stk->top--;
        pelem = stk->data[stk->top];
        return pelem;
    }
    else
    {
        printf("Stack is empty!\n");
        exit(-5);
        return pelem; // todo exit
    }
}

Complex GetComplexStackTop(ComplexStack *stk)
{
    if(stk->top > 0)
    {
        return stk->data[stk->top - 1];
    }
    else
    {
        printf("Stack is empty!\n");
    }
}
