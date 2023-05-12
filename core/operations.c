#include <stdio.h>
#include <math.h>
#include <string.h>
#include "token.h"
#include "complex.h"
#include "operations.h"

Complex* unary_operations(Token *token, Complex *x) {
    if (strcmp(token->value, "cos") == 0)
    {
        x->real = cos(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "sin") == 0)
    {
        x->real = sin(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "tg") == 0)
    {
        x->real = tan(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "log") == 0)  // log by 2
    {
       x->real = log(x->real) / log(2);
       x->imag = 0;
       return x;
    }
    if (strcmp(token->value, "ln") == 0)
    {
        x->real = log(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "sqrt") == 0)
    {
        x->real = sqrt(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "abs") == 0)
    {
        x->real = abs(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "exp") == 0)
    {
        x->real = exp(x->real);
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "real") == 0)
    {
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "imag") == 0)
    {
        x->real = 0;
        return x;
    }
    if (strcmp(token->value, "mag") == 0)
    {
        x->real = sqrt(pow(x->real, 2) + pow(x->imag, 2));
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "phase") == 0)
    {
        x->real = atan(x->imag / x->real) * 57.29578;
        x->imag = 0;
        return x;
    }
    if (strcmp(token->value, "~") == 0)
    {
        x->real *= -1;
        x->imag *= -1;
        return x;
    }
}

Complex binary_operations(Token *token, Complex *value1, Complex *value2) {
    if (strcmp(token->value, "+") == 0)
    {
        return ComplexAdd(*value1, *value2);
    }
    if (strcmp(token->value, "-") == 0)
    {
        return ComplexSub(*value1, *value2);
    }
    if (strcmp(token->value, "*") == 0)
    {
        return ComplexMul(*value1, *value2);
    }
    if (strcmp(token->value, "/") == 0)
    {
        return ComplexDiv(*value1, *value2);
    }
    if (strcmp(token->value, "^") == 0)
    {
        value1->real = pow(value1->real, value2->real);
        value1->imag = 0;
        return *value1;
    }
}
