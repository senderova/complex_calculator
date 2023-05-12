#include "varibleManager.h"
#include <stdio.h>
#include <stdlib.h>

Complex* eval(Variable *var, int num_of_vars, Variable pool[num_of_vars])
{
    int i = 0;
    while (var->expression.requirement_vars[i] != '\0')
    {
        printf("%c", var->expression.requirement_vars[i]);
        i++;
    }




    Complex* res = (Complex*)malloc(sizeof(Complex));



    return res;
}

Variable create_variable(char *name, char *expression, int *num_of_vars, Variable pool[*num_of_vars])
{
    Variable *var = (Variable*)malloc(sizeof(Variable));
    var->name = name;
    var->expression.exp = expression;
    pool[*num_of_vars] = *var;
    (*num_of_vars)++;
    return *var;
}


void Print_Pool(int num_of_vars, Variable pool[num_of_vars])
{
    for (int i = 0; i < num_of_vars; i++)
    {
        printf("%s ", pool[i].name);
    }
    printf("\n");
}