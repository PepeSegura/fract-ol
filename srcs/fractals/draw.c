#include "fractol.h"

void    draw_fractal(t_fractol *fractol)
{
    if (fractol->mode == MANDELBROT)
        draw_mandelbrot(fractol);
    else if (fractol->mode == JULIA)
        draw_julia(fractol);
}
