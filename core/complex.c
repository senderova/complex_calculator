#include <stdlib.h>
#include "stdio.h"
#include "complex.h"


void PrintComplex(Complex value)
{
    printf("%lf ", value.real);
    if (value.imag > 0)
    {
        printf("+ %lfi\n", value.imag);
    }
    else if (value.imag < 0)
    {
        printf("- %lfi\n", value.imag);
    }
}

Complex ComplexRelated(Complex value)
{
    Complex result;
    result.real = value.real;
    result.imag = -value.imag;
    return result;
}

Complex ComplexAdd(Complex left_operand, Complex right_operand)
{
    Complex result;
    result.real = left_operand.real + right_operand.real;
    result.imag = left_operand.imag + right_operand.imag;
    return result;
}

Complex ComplexSub(Complex left_operand, Complex right_operand)
{
    Complex result;
    result.real = left_operand.real - right_operand.real;
    result.imag = left_operand.imag - right_operand.imag;
    return result;
}

Complex ComplexMul(Complex left_operand, Complex right_operand)
{
    Complex result;
    result.real = left_operand.real*right_operand.real - left_operand.imag*right_operand.imag;
    result.imag = left_operand.real*right_operand.imag + left_operand.imag*right_operand.real;
    return result;
}


Complex ComplexDiv(Complex Numerator , Complex Denominator)
{
    Complex result, numerator;
    numerator = ComplexMul(Numerator, ComplexRelated(Denominator));
    result.real = numerator.real / (Denominator.real*Denominator.real + Denominator.imag*Denominator.imag);
    result.imag = numerator.imag / (Denominator.real*Denominator.real + Denominator.imag*Denominator.imag);
    return result;
}

double Real(Complex value)
{
    return value.real;
}

double Imag(Complex value)
{
    return value.imag;
}
