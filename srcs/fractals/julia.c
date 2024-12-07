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

inline void map_screen_coordinates_julia(int i, int j, t_fractol *fractol)
{
    fractol->screen[i][j].real = (j - SCREEN_WIDTH / 2.0) / (SCREEN_WIDTH / 2.0) * fractol->zoom + fractol->offset_x;  // Scale x to real
    fractol->screen[i][j].imag = (i - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0) * fractol->zoom + fractol->offset_y; // Scale y to imaginary
}

inline int get_color(int *iter, int *max_iter)
{
    if (*iter == *max_iter)
        return (0x000000);
    return (0xFFFFFF - (*iter * 255 / *max_iter));
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
            map_screen_coordinates_julia(i, j, fract);
            iter = julia(fract->max_iter, &fract->screen[i][j], &(t_complex ){.real=-0.835, .imag=-0.2321});  // Pass fixed c
            mlx_put_pixel(fract->img, j, i, get_color(&iter, &fract->max_iter));
            j++;
        }
        i++;
    }
    printf("FINISHED PRINTING JULIA SET\n");
}
