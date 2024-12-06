#include "fractol.h"

t_complex   add(t_complex a, t_complex b)
{
    return ((t_complex){a.real + b.real, a.imag + b.imag});
}

t_complex   substract(t_complex a, t_complex b)
{
    return ((t_complex){a.real - b.real, a.imag - b.imag});
}

t_complex   mult(t_complex a, t_complex b)
{
    return ((t_complex)
    {
        (a.real * b.real) - (a.imag * b.imag),
        (a.real * b.imag) + (a.imag * b.real)
    });
}

t_complex   division(t_complex a, t_complex b)
{
    const double denominator = (b.real * b.real) + (b.imag * b.imag);

    return ((t_complex)
    {
        ((a.real * b.real) + (a.imag * b.imag)) / denominator,
        ((a.imag * b.real) - (a.real * b.imag)) / denominator
    });
}

double   magnitude(t_complex a)
{
    return (sqrt((a.real * a.real) + (a.imag * a.imag)));
}

void    printComplex(t_complex a)
{
    printf("Complex: %f + %fi\n", a.real, a.imag);
}
