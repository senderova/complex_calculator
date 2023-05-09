#pragma once

typedef struct
{
    double real;
    double imag;
} Complex;

void PrintComplex(Complex value);

Complex ComplexRelated(Complex value);

Complex ComplexAdd(Complex left_operand, Complex right_operand);

Complex ComplexSub(Complex left_operand, Complex right_operand);

Complex ComplexMul(Complex left_operand, Complex right_operand);

Complex ComplexDiv(Complex left_operand, Complex right_operand);

double Real(Complex value);

double Imag(Complex value);
