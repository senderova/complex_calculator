#include "stackAndTokens.h"
#include "config.h"
#include <stdio.h>
#include <stdlib.h>

void InitializeToken(Token *token){
    for (int i = 0; i < MAX_TOKEN_LEN; i++)
    {
        token->value[i] = '\0';
    }
}

Token* NewToken(){
    Token *p_token = malloc(sizeof(Token));
    InitializeToken(p_token);
    return p_token;
}

void AssignToken(Token *token, char *value){
    int i = 0;
    while ((value[i] != '\0') && (i < MAX_TOKEN_LEN))
    {
        token->value[i] = value[i];
        i++;
    }
}

void PrintToken(Token *tk)
{
    printf("<Token: ");
    int i = 0;
    while ((i < MAX_TOKEN_LEN) && (tk->value[i] != '\0'))
    {
        printf("%c", tk->value[i]);
        i++;
    }
    printf(">");
}

void InitializeStack(Stack *stk)
{
    stk->top = 0;
}

Stack* NewStack(){
    Stack *p_stk = malloc(sizeof(Stack));
    InitializeStack(p_stk);
    return p_stk;
}

void PushStack(Stack *stk, Token *tk)
{
    if (stk->top < MAX_STACK_SIZE) {
        stk->data[stk->top] = tk;
        stk->top++;
    }
    else
    {
        printf("Stack overflow error, total amount of elements is: %d !\n", stk->top);
    }
}

Token* PopStack(Stack *stk)
{
    Token* pelem;
    if(stk->top > 0)
    {
        stk->top--;
        pelem = stk->data[stk->top];
        return pelem;
    }
    else
    {
        printf("Stack is empty!\n");
        return pelem;
    }
}

Token* GetStackTop(Stack *stk)
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

int GetCountStack(Stack *stk)
{
    return stk->top;
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

void PrintStack(Stack *stk) {
    int i;
    i = stk->top;
    if(IsStackEmpty(stk) == 1) return;
    do {
        i--;
        PrintToken(stk->data[i]);
    } while(i > 0);
}
