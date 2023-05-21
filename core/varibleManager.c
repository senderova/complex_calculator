#include "varibleManager.h"
#include <stdio.h>
#include <stdlib.h>
#include "token.h"
#include <string.h>
#include "stack.h"
#include "operations.h"
#include "toPostfix.h"
#include "string.h"


int TokenTypeIsGood(Token token)
{
    if (strcmp(token.type, "VARIABLE") == 0)
    {return 1;}
    if (strcmp(token.type, "NUMBER") == 0)
    {return 1;}
    if (strcmp(token.type, "COMPLEX") == 0)
    {return 1;}
    if (strcmp(token.type, "FUNCTION") == 0)
    {return 1;}
    if (strcmp(token.type, "OPERATOR") == 0)
    {return 1;}
    return 0;
}

int getVariableIndex(char* target, int num_of_vars, Variable pool[num_of_vars])
{
    for (int i = 0; i < num_of_vars; i++)
    {
        if (strcmp(target, pool[i].name) == 0)
        {
            return i;
        }
    }
    return -1;
}

Complex FromTokenToComplex(Token* token, int num_of_vars, Variable pool[num_of_vars])
{
    Complex *result = malloc(sizeof(Complex));
    if (strcmp(token->type, "NUMBER")==0)
    {
        result->real = strtod(token->value, NULL);
        result->imag = 0;
        return *result;
    }
    if (strcmp(token->type, "COMPLEX")==0)
    {
        result->real = 0;
        if (strlen(token->value) == 1)
        {
            result->imag = 1;
        }
        else
        {
            char buffer[MAX_TOKEN_VALUE_LEN];
            strcpy(buffer, token->value);
            buffer[strlen(buffer)-1] = '\0';
            result->imag = strtod(buffer, NULL);
        }
        return *result;
    }
    if (strcmp(token->type, "VARIABLE")==0)
    {
        int index = getVariableIndex(token->value, num_of_vars, pool);
        if (index != -1)
        {
            if (pool[index].expression.is_calculated == 0)
            {
                return *result;
            }
            Complex temp = pool[getVariableIndex(token->value, num_of_vars, pool)].expression.value;
            result->real = temp.real;
            result->imag = temp.imag;

            return *result;
        }
    }
    return *result;
}


Complex CalculateExpression(Expression expression, int num_of_vars, Variable pool[num_of_vars])
{
    // 0)
    Complex* result = malloc(sizeof(Complex));
    result->real = 0.123456789;
    result->imag = 0.123456789;

    // 1) get a len of array with tokens
    int len_of_tokens = 0;
    for (int i = 0; TokenTypeIsGood(expression.exp[i]); i++){len_of_tokens++;}

    // 2) Init the stack
    ComplexStack reverse_rpn;
    InitializeComplexStack(&reverse_rpn);

    // 3) Reverse calculation
    for (int i = 0; i < len_of_tokens; i++)
    {
        if (strcmp(expression.exp[i].type, "FUNCTION")==0)
        {
            Complex current_token = PopComplexStack(&reverse_rpn);
            Complex *new_token = malloc(sizeof(Complex));
            new_token = unary_operations(&expression.exp[i], &current_token);
            PushComplexStack(&reverse_rpn, new_token);
            continue;
        }

        if (strcmp(expression.exp[i].type, "OPERATOR")==0)
        {
            // Prepare data
            Complex right_value = PopComplexStack(&reverse_rpn);
            Complex left_value = PopComplexStack(&reverse_rpn);
            // Calculate the result
            left_value = binary_operations(&expression.exp[i], &left_value, &right_value);
            PushComplexStack(&reverse_rpn, &left_value);
            continue;
        }

        // check variable
        if (strcmp(expression.exp[i].type, "VARIABLE") == 0)
        {
            int index = getVariableIndex(expression.exp[i].value, num_of_vars, pool);
            if (index == -1 || pool[index].expression.is_calculated == 0)
            {
                return *result;
            }
        }
        Complex *next = malloc(sizeof(Complex));
        Complex converted = FromTokenToComplex(&expression.exp[i], num_of_vars, pool);
        next->real = converted.real;
        next->imag = converted.imag;
        PushComplexStack(&reverse_rpn, next);
    }
    if (reverse_rpn.top == 1)
    {
        Complex temp = PopComplexStack(&reverse_rpn);
        result->real = temp.real;
        result->imag = temp.imag;
    }
    return *result;
}

Complex* eval(Token *token_pool, int *num_of_vars, Variable pool[*num_of_vars])
{
    // 0) Recalculate previous variables
    int all_calculated = 0;
    while (!all_calculated)
    {
        all_calculated = 1;
        for (int i = 0; i < *num_of_vars; i++)
        {
            if (pool[i].expression.is_calculated){ continue;}
            pool[i].expression.value = CalculateExpression(pool[i].expression, *num_of_vars, pool);
            if (pool[i].expression.value.real != 0.123456789 && pool[i].expression.value.imag != 0.123456789)
            {
                pool[i].expression.is_calculated = 1;
                // printf("Variable <%s> has been evaluated!\n", pool[i].name); #todo
                all_calculated = 0;
            }
        }
    }
    // 1) Get a len of array with tokens
    int len_of_tokens = 0;
    for (int i = 0; TokenTypeIsGood(token_pool[i]); i++){len_of_tokens++;}

    /* There are three cases
     *  1) assign
     *  2) return value
     *  3) just expression
     * */

    // First case
    int is_assign = 0;
    for (int i = 0; i < len_of_tokens; i++)
    {
        if (strcmp(token_pool[i].value, "=") == 0)
        {
            is_assign = 1;
            break;
        }
    }
    if (is_assign){
        if (strcmp(token_pool[0].type, "VARIABLE") == 0 && strcmp(token_pool[1].value, "=") == 0)
        {
            // Assign
            int index = getVariableIndex(token_pool[0].value, *num_of_vars, pool);
            if (index != -1)
            {
                // Variable exists
                // printf("Variable <%s> already exists, it will be overwrite\n", token_pool[0].value); #todo
                pool[index].expression.is_calculated = 0;
                pool[index].expression.exp = token_pool + 2;
                pool[index].expression.value = CalculateExpression(pool[index].expression, *num_of_vars, pool);
                if (pool[index].expression.value.real != 0.123456789 && pool[index].expression.value.imag != 0.123456789)
                {pool[index].expression.is_calculated = 1;}
            }
            else
            {
                // Variable does not exist
                for (int i = 2; i < len_of_tokens; i++)
                {
                    if (strcmp(token_pool[i].value, token_pool[0].value) == 0)
                    {
                        printf("Invalid Expression (maybe this expression contains a recursive definition)!\n");
                        return NULL;
                    }
                }


                printf("Variable <%s> is assigned\n", token_pool[0].value);
                Token* new = calloc(len_of_tokens, sizeof(Token));
                for (int i = 0; i < len_of_tokens; i++)
                {
                    new[i] = token_pool[i];
                }
                char name[strlen(token_pool[0].value)+1];
                strcpy(name, token_pool[0].value);
                create_variable(name, new+2, num_of_vars, pool);
                pool[*num_of_vars].expression.is_calculated = 0;
            }
        }
        else
        {
            printf("Invalid Assign Expression!\n");
        }
    }

    // Second case
    else if (strcmp(token_pool[0].type, "VARIABLE") == 0 && len_of_tokens == 1)
    {
        // return value
        int index = getVariableIndex(token_pool[0].value, *num_of_vars, pool);
        if (index!= -1)
        {
            // Variable exists

            // is calculated
            if (pool[index].expression.is_calculated)
            {
                PrintComplex(pool[index].expression.value);
            }
            // does not calculate
            else
            {
                printf("It cannot be calculated now\n");
            }
        }
        else
        {
            // Variable does not exist
            printf("Unknown variable <%s>\n", token_pool[0].value);
        }
    }

    else
    {
//        // check expression`s variables
//        int is_calculative = 1;
//        for (int i = 0; i < len_of_tokens; i++)
//        {}


        Complex* result = malloc(sizeof(Complex));
        result->real = 0.123456789;
        result->imag = 0.123456789;

        // 2) Init the stack
        ComplexStack reverse_rpn;
        InitializeComplexStack(&reverse_rpn);

        // 3) Reverse calculation
        for (int i = 0; i < len_of_tokens; i++)
        {
            if (strcmp(token_pool[i].type, "FUNCTION")==0)
            {
                Complex current_token = PopComplexStack(&reverse_rpn);
                Complex *new_token = malloc(sizeof(Complex));
                new_token = unary_operations(&token_pool[i], &current_token);
                PushComplexStack(&reverse_rpn, new_token);
                continue;
            }

            if (strcmp(token_pool[i].type, "OPERATOR")==0)
            {
                // Prepare data
                Complex right_value = PopComplexStack(&reverse_rpn);
                Complex left_value = PopComplexStack(&reverse_rpn);
                // Calculate the result
                left_value = binary_operations(&token_pool[i], &left_value, &right_value);
                PushComplexStack(&reverse_rpn, &left_value);
                continue;
            }
            // check variable
            if (strcmp(token_pool[i].type, "VARIABLE") == 0)
            {
                int index = getVariableIndex(token_pool[i].value, *num_of_vars, pool);
                if (index == -1 || pool[index].expression.is_calculated == 0)
                {
                    break;
                }
            }

            Complex *next = malloc(sizeof(Complex));
            Complex converted = FromTokenToComplex(&token_pool[i], *num_of_vars, pool);
            next->real = converted.real;
            next->imag = converted.imag;
            PushComplexStack(&reverse_rpn, next);
        }
        if (reverse_rpn.top == 1)
        {
            Complex temp = PopComplexStack(&reverse_rpn);
            result->real = temp.real;
            result->imag = temp.imag;
            PrintComplex(*result);
        }
        else
        {
            printf("Invalid expression\n");
        }
    }
}






Variable create_variable(char *name, Token *expression, int *num_of_vars, Variable pool[*num_of_vars])
{
    Variable *var = (Variable*)malloc(sizeof(Variable));
    char *new_name = calloc(strlen(name)+1, sizeof(char));
    strcpy(new_name, name);
    var->name = new_name;
    var->expression.exp = expression;
    var->expression.is_calculated = 0;
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

void PrintExpression(Expression expression)
{
    for (int i = 0; TokenTypeIsGood(expression.exp[i]); i++)
    {
        printf("%s ", expression.exp[i].value);
    }
    printf("\n");
}