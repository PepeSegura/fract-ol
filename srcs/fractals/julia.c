#include "fractol.h"

int julia(int max_iter, t_complex *z, t_complex *c)
{
    t_complex z_square;
    int       iterations;

    // Julia formula z_n+1 = z_n^2 + c
    iterations = 0;
    while (1)
    {
        z_square.real = z->real * z->real;
        z_square.imag = z->imag * z->imag;
        if ((z_square.real + z_square.imag) >= 4.0 || iterations >= max_iter)
            return (iterations);
        z->imag = 2.0 * z->real * z->imag + c->imag;
        z->real = z_square.real - z_square.imag + c->real;
        iterations++;
    }
    return iterations;
}

void draw_julia(t_fractol *fract)
{
    int         i;
    int         j;
    int         iter;

    i = 0;
    while (i < SCREEN_HEIGHT)
    {
        j = 0;
        while (j < SCREEN_WIDTH)
        {
            map_screen_coordinates(i, j, fract);
            iter = julia(fract->max_iter, &fract->screen[i][j], &fract->julia);  // Pass fixed c
            mlx_put_pixel(fract->img, j, i, get_color(&iter, &fract->max_iter));
            j++;
        }
        i++;
    }
    printf("FINISHED PRINTING JULIA SET\n");
}
