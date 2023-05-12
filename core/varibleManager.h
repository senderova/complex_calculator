#pragma once
#include "complex.h"

typedef struct {
    char* exp;
    char* requirement_vars;
    Complex value;
} Expression;

typedef struct {
    char* name;
    Expression expression;
} Variable;

Variable create_variable(char *name, char *expression, int *num_of_vars, Variable pool[*num_of_vars]);

Complex* eval(Variable *var, int num_of_vars, Variable pool[num_of_vars]);

void Print_Pool(int num_of_vars, Variable pool[num_of_vars]);
