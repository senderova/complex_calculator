#pragma once
#include "config.h"
#define MAX_TOKEN_LEN 100
#define MAX_STACK_SIZE 100000


typedef struct {
    char value[MAX_TOKEN_LEN];
} Token;


typedef struct Stack{
    Token *data[MAX_STACK_SIZE];
    struct Stack *next;
    int top;
} Stack;

void InitializeToken(Token *token);

Token* NewToken();

void AssignToken(Token *token, char *value);

void PrintToken(Token *tk);

Stack* NewStack();

void InitializeStack(Stack *stk);

void PushStack(Stack *stk, Token *tk);

Token* PopStack(Stack *stk);

Token* GetStackTop(Stack *stk);

int GetCountStack(Stack *stk);

int IsStackEmpty(Stack *stk);

void PrintStack(Stack *stk);
