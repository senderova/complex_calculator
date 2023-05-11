#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKEN_LEN 100
#define MAX_STACK_SIZE 1000

typedef struct {
    char type[10];
    char value[MAX_TOKEN_LEN];
} Token;

typedef struct Stack {
    Token data[MAX_STACK_SIZE];
    int top;
} Stack;

void InitializeToken(Token *token){
    for (int i = 0; i < MAX_TOKEN_LEN; i++)
    {
        token->value[i] = '\0';
    }
    for (int i = 0; i < 10; i++)
    {
        token->type[i] = '\0';
    }
}

void InitializeStack(Stack *stk)
{
    stk->top = 0;
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
        return pelem;
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

int operation_priority(char ch)
{
    if(ch == '(')
        return 0;
    else if(ch == '+' || ch == '-')
        return 1;
    else if(ch == '*' || ch == '/' || ch == '%')
        return 2;
    else if(ch == '^')
        return 3;
    else if (ch == '~')
        return 4;
    return 5;
}

Token CreateToken(char *type, char *value)
{
    Token token;
    InitializeToken(&token);
    strcpy(token.type, type);
    strcpy(token.value, value);
    return token;
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
        if ((strcmp(value, "%") == 0))
        {  return "OPERATOR"; }
        if ((strcmp(value, "^") == 0))
        {  return "OPERATOR"; }
        if ((strcmp(value, "~") == 0))
        {  return "OPERATOR"; }
        // error
        printf("Error: unknown symbol: %s\n", value);
        exit(-1);
    }
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
            if(infix[i] == '(')
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

int main(){
    char infix[100], postfix[100];
    gets(infix);
    infix_to_postfix(infix, postfix);
    printf("%s",postfix);
    printf("\n");
    return 0;
}


