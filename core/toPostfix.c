#include<ctype.h>
#include "stack.h"

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

