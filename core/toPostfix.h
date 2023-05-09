#pragma once

#include<stdio.h>
#include<ctype.h>
#include<stack.h>


int operation_priority(char ch);

void infix_to_postfix(char infix[],char postfix[]);