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
    Complex* result = malloc(sizeof(Complex));
    result->real = 0.123456789;
    result->imag = 0.123456789;
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
            strcpy(token->value, buffer);
            buffer[strlen(buffer)-2] = '\0';
            result->imag = strtod(token->value, NULL);
        }
        return *result;
    }
    if (strcmp(token->type, "VARIABLE")==0)
    {
        if (getVariableIndex(token->value, num_of_vars, pool) != -1)
        {
            Complex temp = pool[getVariableIndex(token->value, num_of_vars, pool)].expression.value;
            if (pool[getVariableIndex(token->value, num_of_vars, pool)].expression.is_calculated == 0)
            {return *result;}
            result->imag = temp.imag;
            result->real = temp.real;
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
            if (reverse_rpn.top == 0) {return *result;}
            Complex current_token = PopComplexStack(&reverse_rpn);
            if (current_token.imag == 0.123456789 && current_token.real == 0.123456789)
            {return *result;}
            Complex *new_token = malloc(sizeof(Complex));
            new_token = unary_operations(&expression.exp[i], &current_token);
            PushComplexStack(&reverse_rpn, new_token);
            continue;
        }

        if (strcmp(expression.exp[i].type, "OPERATOR")==0)
        {
            // Prepare data
            if (reverse_rpn.top == 1){return *result;}
            Complex right_value = PopComplexStack(&reverse_rpn);
            if (right_value.imag == 0.123456789 && right_value.real == 0.123456789)
            {return *result;}
            Complex left_value = PopComplexStack(&reverse_rpn);
            if (left_value.imag == 0.123456789 && left_value.real == 0.123456789)
            {return *result;}
            // Calculate the result
            left_value = binary_operations(&expression.exp[i], &left_value, &right_value);
            PushComplexStack(&reverse_rpn, &left_value);
            continue;
        }
        Complex *next = malloc(sizeof(Complex));
        Complex converted = FromTokenToComplex(&expression.exp[i], num_of_vars, pool);
        if (converted.imag == 0.123456789 && converted.real == 0.123456789)
        {return *result;}
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
    for (int j = 0; j< COSTblL; j++)
    {
    for (int i = 0; i < *num_of_vars; i++)
    {
        if (pool[i].expression.is_calculated){ continue;}
        pool[i].expression.value = CalculateExpression(pool[i].expression, *num_of_vars, pool);
        if (pool[i].expression.value.real != 0.123456789 && pool[i].expression.value.imag != 0.123456789)
        {pool[i].expression.is_calculated = 1;}
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
    if (strcmp(token_pool[0].type, "VARIABLE") == 0 && strcmp(token_pool[1].value, "=") == 0)
    {
        // Assign
        int index = getVariableIndex(token_pool[0].value, *num_of_vars, pool);
        if (index != -1)
        {
            // Variable exists
            printf("Variable <%s> already exists, it will be overwrite\n", token_pool[0].value);
            pool[index].expression.is_calculated = 0;
            pool[index].expression.exp = token_pool + 2;
            pool[index].expression.value = CalculateExpression(pool[index].expression, *num_of_vars, pool);
            if (pool[index].expression.value.real != 0.123456789 && pool[index].expression.value.imag != 0.123456789)
            {pool[index].expression.is_calculated = 1;}
        }
        else
        {
            // Variable does not exist
            printf("Variable <%s> is assigned\n", token_pool[0].value);
            Token* new = malloc(len_of_tokens*sizeof(Token));
            for (int i = 0; i < len_of_tokens; i++)
            {new[i] = token_pool[i];}
            char name[strlen(token_pool[0].value)+1];
            strcpy(name, token_pool[0].value);
            create_variable(name, new+2, num_of_vars, pool);
            pool[*num_of_vars].expression.is_calculated = 0;
            pool[*num_of_vars].expression.value.real = 0.123456789;
            pool[*num_of_vars].expression.value.imag = 0.123456789;
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
                //PrintExpression(pool[index].expression);
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
        // third case, just calculate
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
                if (reverse_rpn.top == 0){return result;}
                Complex current_token = PopComplexStack(&reverse_rpn);
                Complex *new_token = malloc(sizeof(Complex));
                new_token = unary_operations(&token_pool[i], &current_token);
                PushComplexStack(&reverse_rpn, new_token);
                continue;
            }

            if (strcmp(token_pool[i].type, "OPERATOR")==0)
            {
                // Prepare data
                if (reverse_rpn.top == 1){return result;}
                Complex right_value = PopComplexStack(&reverse_rpn);
                Complex left_value = PopComplexStack(&reverse_rpn);
                // Calculate the result
                left_value = binary_operations(&token_pool[i], &left_value, &right_value);
                PushComplexStack(&reverse_rpn, &left_value);
                continue;
            }
            Complex *next = malloc(sizeof(Complex));
            Complex converted = FromTokenToComplex(&token_pool[i], *num_of_vars, pool);
            // cannot be calculated
            if (converted.real == 0.123456789 && converted.imag == 0.123456789)
            { return result;}
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
        printf("%s ", expression.exp->value);
    }
    printf("\n");
}