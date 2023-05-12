#pragma once

#include "config.h"

typedef struct Stack
{
    int data[MAX_STACK_SIZE];
    int top;
}Stack;

void Initialize(Stack *stack);

int IsEmpty(Stack *stack);

int IsFull(Stack *stack);

void Push(Stack *stack, int x);

int Pop(Stack *stack);

int GetTop(Stack *stack);