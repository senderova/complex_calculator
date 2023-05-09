#include<ctype.h>
#include "stack.h"
#include "toPostfix.h"
#include "utils.h"
#include <stdlib.h>
#include <string.h>


int operation_priority(char ch)
{
    if(ch == '(')
        return 0;
    else if(ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/')
        return 2;
    else if(ch == '^')
        return 3;
    else if(ch == '~')
        return 4;
    return 5;
}

void infix_to_postfix(char infix[],char postfix[])
{
    Stack stack;
    char x, token;
    int i, j = 0;
    Initialize(&stack);
    for(i = 0; infix[i] != '\0'; i++)
    {
        token = infix[i];
        if(isalnum(token) || token == '.')
        {
            postfix[j++] = token;
        }
        else {
            postfix[j++] = ' ';
            if(token=='(')
            {
                Push(&stack,'(');
            }
            else if(token == ')')
                while((x = Pop(&stack))!='(')
                {
                    postfix[j++] = x;
                    postfix[j++] = ' ';
                }
            else
            {
                if (token == '-' && (i == 0 || infix[i - 1] == '('))
                {
                    token = '~';
                }
                while(operation_priority(token) <= operation_priority(GetTop(&stack)) && !IsEmpty(&stack))
                {
                    x = Pop(&stack);
                    postfix[j++] = x;
                    postfix[j++] = ' ';
                }
                Push(&stack,token);
            }
        }
    }
    while(!IsEmpty(&stack))
    {
        x = Pop(&stack);
        postfix[j++] = x;
        postfix[j++] = ' ';
    }
    postfix[j]='\0';
}

int strIsAlpha(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isalpha(str[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int strIsDigit(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isdigit(str[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

Token* CreateToken(char* type, char* value)
{
    Token* token = malloc(sizeof(Token));
    token->type = type;
    token->value = value;
    return token;
}

char* GetType(char* value)
{
    if (strIsDigit(value))
    {
        // int
        return "NUMBER";
    }
    else if (strIsAlpha(value))
    {
        // Functions
        if ((strcmp(value, "sin") == 0))
        { return "FUNCTION"; }
        if ((strcmp(value, "cos") == 0))
        { return "FUNCTION"; }
        if ((strcmp(value, "ln") == 0))
        {  return "FUNCTION"; }
        if ((strcmp(value, "exp") == 0))
        {  return "FUNCTION"; }

        // Variables
        return "VARIABLE";
    }
    else
    {
        // operators
        if ((strcmp(value, "+") == 0))
        {  return "OPERATOR"; }
        if ((strcmp(value, "-") == 0))
        {  return "OPERATOR"; }
        if ((strcmp(value, "*") == 0))
        {  return "OPERATOR"; }
        if ((strcmp(value, "/") == 0))
        {  return "OPERATOR"; }
        // error
        printf("Error: unknown symbol: %s\n", value);
        exit(-1);
    }
}