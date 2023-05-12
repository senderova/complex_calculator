#pragma once

#include<stdio.h>
#include<ctype.h>
#include<stack.h>
#include<stdlib.h>

int operation_priority(char ch);

void infix_to_postfix(char infix[],char postfix[]);

char* GetType(char* value);

int strIsAlpha(char *str);

int strIsDigit(char *str);

int strIsComplex(char *str);