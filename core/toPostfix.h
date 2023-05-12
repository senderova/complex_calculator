#pragma once

#include<stdio.h>
#include<ctype.h>
#include<stack.h>
#include<stdlib.h>

typedef struct {
    char* type;
    char* value;
} Token;

int operation_priority(char ch);

void infix_to_postfix(char infix[],char postfix[]);

Token* CreateToken(char* name, char* value);

char* GetType(char* value);