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

void infix_to_postfix(char *infix, char *postfix)
{
    Stack stack;
    InitializeStack(&stack);
    Token token, x;
    InitializeToken(&x);
    int i = 0, j = 0;
    while(infix[i] != '\0')
    {
        // space skipping
        if (infix[i] == ' ')
        {
            i++;
            continue;
        }
        InitializeToken(&token);
        if(isalnum(infix[i]))
        {
            int len = 0;
            while(isalnum(infix[i]) || infix[i] == '.')
            {
                token.value[len++] = infix[i];
                i++;
            }
            if (strcmp(GetType(token.value), "FUNCTION") == 0)
            {
                token = CreateToken(GetType(token.value), token.value);
                token.value[len] = '\0';
                PushStack(&stack, &token);
            }
            else
            {
                for (int q = 0; q < len; q++)
                {
                    postfix[j++] = token.value[q];
                }
                postfix[j++] = ' ';
            }
        }
        else
        {
            if (infix[i] == '=') {
                postfix[j++] = '=';
                postfix[j++] = ' ';
            }
            else if(infix[i] == '(')
            {
                token = CreateToken("OPERATOR", "(");
                PushStack(&stack, &token);
            }
            else if(infix[i] == ')')
            {
                x = PopStack(&stack);
                while(x.value[0] != '(')
                {
                    int w = 0;
                    while(x.value[w] != '\0')
                    {
                        postfix[j++] = x.value[w];
                        w++;
                    }
                    postfix[j++] = ' ';
                    x = PopStack(&stack);
                }
            }
            else
            {
                if (infix[i] == '-' && (i == 0 || infix[i - 1] == '('))
                {
                    infix[i] = '~';
                }
                while(!IsStackEmpty(&stack) && ((strcmp(GetStackTop(&stack).type, "FUNCTION") == 0) || (operation_priority(infix[i]) <= operation_priority(GetStackTop(&stack).value[0]))))
                {
                    x = PopStack(&stack);
                    if(strcmp(x.type, "FUNCTION") == 0)
                    {
                        int w = 0;
                        while(x.value[w] != '\0')
                        {
                            postfix[j++] = x.value[w];
                            w++;
                        }
                    }
                    else
                    {
                        postfix[j++] = ' ';
                        postfix[j++] = x.value[0];
                    }
                }
                char str[10];
                for (int h = 0; h < 10; ++h)
                {
                    str[i] = '\0';
                }
                str[0] = infix[i];
                token = CreateToken(GetType(str), str);;
                PushStack(&stack, &token);
            }
            i++;
        }
        postfix[j++] = ' ';
    }
    while(!IsStackEmpty(&stack))
    {
        x = PopStack(&stack);
        if(strcmp(x.type, "FUNCTION") == 0)
        {
            int w = 0;
            while(x.value[w] != '\0')
            {
                postfix[j++] = x.value[w];
                w++;
            }
        }
        else
        {
            postfix[j++] = x.value[0];
        }
        postfix[j++] = ' ';
    }
    postfix[j]='\0';
}


int strIsAlpha(char *str)
{
    for (int i = 0; i < strlen(str); i++)
    {
        if (isascii(str[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int strIsDigit(char *str)
{
    int flag = 0;
    for (int i = 0; i < strlen(str); i++)
    {
        if (str[i] == '.')
        {
            if (flag == 0)
            {
                flag = 1;
            }
            else
            {
                return 0;
            }
        }
        else if (isdigit(str[i]) == 0)
        {
            return 0;
        }
    }
    return 1;
}

int strIsComplex(char *str)
{
    int flag = 0;
    int complex = 0;
    for (int i = 0; i < strlen(str)-1; i++)
    {
        if (str[i] == '.')
        {
            if (flag == 0)
            {
                flag = 1;
            }
            else
            {
                return 0;
            }
        }
        else if (isdigit(str[i]) == 0)
        {
            return 0;
        }
    }
    if (str[strlen(str)-1] == 'i')
    {
        return 1;
    }
    return 0;
}

char* GetType(char* value)
{
    if (strIsDigit(value))
    {
        // int
        return "NUMBER";
    }
    else if ((strIsComplex(value)))
    {
        // complex
        return "COMPLEX";
    }
    // Functions
    if ((strcmp(value, "cos") == 0))
    { return "FUNCTION"; }
    if ((strcmp(value, "sin") == 0))
    { return "FUNCTION"; }
    if ((strcmp(value, "sqrt") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "log") == 0))  // log by 2
    {  return "FUNCTION"; }
    if ((strcmp(value, "ln") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "sqrt") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "abs") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "exp") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "real") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "imag") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "mag") == 0))
    {  return "FUNCTION"; }
    if ((strcmp(value, "phase") == 0))
    {  return "FUNCTION"; }

    // operators
    if ((strcmp(value, "+") == 0))
    {  return "OPERATOR"; }
    if ((strcmp(value, "-") == 0))
    {  return "OPERATOR"; }
    if ((strcmp(value, "*") == 0))
    {  return "OPERATOR"; }
    if ((strcmp(value, "/") == 0))
    {  return "OPERATOR"; }
    if ((strcmp(value, "=") == 0))
    {  return "OPERATOR"; }
    if ((strcmp(value, "^") == 0))
    {  return "OPERATOR"; }

    // Variables
    if (strIsAlpha(value))
    { return "VARIABLE"; }
    // error
    printf("Error: unknown symbol: %s\n", value);
    exit(-1);
}