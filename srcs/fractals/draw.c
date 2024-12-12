#include "fractol.h"

void map_screen_coordinates(int i, int j, t_fractol *fractol)
{
    fractol->screen[i][j].real = (j - SCREEN_WIDTH / 2.0) / (SCREEN_WIDTH / 2.0) * fractol->zoom + fractol->offset_x;  // Scale x to real
    fractol->screen[i][j].imag = (i - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0) * fractol->zoom + fractol->offset_y; // Scale y to imaginary
}

int get_color(int *iter, double *max_iter)
{
    // If the point is inside the Mandelbrot set, return black (iter >= max_iter)
    if (*iter >= *max_iter)
        return (0x000000FF);  // Fully transparent black (0xRRGGBBAA)
    
    // Normalize iteration count
    double t = (double)*iter / *max_iter;

    // Create more drastic color shifts by using sine/cosine functions
    unsigned char r = (int)((sin(t * 3.0 * M_PI) + 1.0) * 127.5);  // Red channel oscillates with a sine wave
    unsigned char g = (int)((sin(t * 2.0 * M_PI) + 1.0) * 127.5);  // Green channel oscillates with a different sine wave
    unsigned char b = (int)((sin(t * 1.5 * M_PI) + 1.0) * 127.5);  // Blue channel also varies

    // Combine the channels into a single 32-bit color (0xRRGGBBAA)
    return (r << 16) | (g << 8) | b | 0x000000FF;  // Set Alpha to 255 (opaque)
}

void    draw_fractal(t_fractol *fractol)
{
    if (fractol->mode == MANDELBROT)
        draw_mandelbrot(fractol);
    else if (fractol->mode == JULIA)
        draw_julia(fractol);
}
