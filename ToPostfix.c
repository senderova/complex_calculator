#include<stdio.h>
#include<ctype.h>

#define MAX_STACK_SIZE 1000

typedef struct Stack
{
    int data[MAX_STACK_SIZE];
    int top;
}Stack;

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
    return 4;
}

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

void infix_to_postfix(char infix[],char postfix[])
{
    Stack stack;
    char x, token;
    int i, j = 0;
    Initialize(&stack);
    for(i = 0; infix[i] != '\0'; i++)
    {
        token = infix[i];
        if(isalnum(token))
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

int main(){
    char infix[100],postfix[100];
    gets(infix);
    infix_to_postfix(infix,postfix);
    printf("%s",postfix);
    return 0;
}

