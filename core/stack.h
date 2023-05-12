#pragma once

#include "config.h"
#include "token.h"
#include "complex.h"

typedef struct Stack {
    Token data[MAX_STACK_SIZE];
    int top;
} Stack;

typedef struct {
    Complex data[MAX_STACK_SIZE];
    int top;
} ComplexStack;


void InitializeStack(Stack *stack);

int IsStackEmpty(Stack *stk);

void PushStack(Stack *stk, Token *tk);

Token PopStack(Stack *stk);

Token GetStackTop(Stack *stk);

void InitializeComplexStack(ComplexStack *stack);

int IsComplexStackEmpty(ComplexStack *stk);

void PushComplexStack(ComplexStack *stk, Complex *tk);

Complex PopComplexStack(ComplexStack *stk);

Complex GetComplexStackTop(ComplexStack *stk);