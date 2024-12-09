/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/09 13:19:29 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mandelbrot(int max_iter, t_complex *c)
{
    t_complex   z;
    t_complex   z_square;
    int         iterations;
    
    // Mandelbrot formula z_n+1 = z_n^2 + c
    z.real = 0.0;
    z.imag = 0.0;
    iterations = 0;
    while (1)
    {
        z_square.real = z.real * z.real;
        z_square.imag = z.imag * z.imag;
        if ((z_square.real + z_square.imag) >= 4.0 || iterations >= max_iter)
            return (iterations);
        z.imag = 2.0 * z.real * z.imag + c->imag;
        z.real = z_square.real - z_square.imag + c->real;
        iterations++;
    } 
    return iterations;
}

inline int get_color(int *iter, double *max_iter)
{
    // If the point is inside the Mandelbrot set, return black (iter >= max_iter)
    if (*iter >= *max_iter)
        return (0x000000FF);  // Fully transparent black (0xRRGGBBAA)
    
    // Normalize iteration count
    double t = (double)*iter / *max_iter;

    // Create more drastic color shifts by using sine/cosine functions
    int r = (int)((sin(t * 3.0 * M_PI) + 1.0) * 127.5);  // Red channel oscillates with a sine wave
    int g = (int)((sin(t * 2.0 * M_PI) + 1.0) * 127.5);  // Green channel oscillates with a different sine wave
    int b = (int)((sin(t * 1.5 * M_PI) + 1.0) * 127.5);  // Blue channel also varies

    // Make sure the RGB values are within bounds (0-255)
    r = r < 0 ? 0 : (r > 255 ? 255 : r);
    g = g < 0 ? 0 : (g > 255 ? 255 : g);
    b = b < 0 ? 0 : (b > 255 ? 255 : b);

    // Combine the channels into a single 32-bit color (0xRRGGBBAA)
    return (r << 16) | (g << 8) | b | 0x000000FF;  // Set Alpha to 255 (opaque)
}

inline void map_screen_cordinates(int i, int j, t_fractol *fractol)
{
    fractol->screen[i][j].real = (j - SCREEN_WIDTH / 2.0) / (SCREEN_WIDTH / 2.0) * fractol->zoom + fractol->offset_x;  // Scale x to real
    fractol->screen[i][j].imag = (i - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0) * fractol->zoom + fractol->offset_y; // Scale y to imaginary
}

void    draw_mandelbrot(t_fractol *fract)
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
            map_screen_cordinates(i, j, fract);
            iter = mandelbrot(fract->max_iter, &fract->screen[i][j]);
            mlx_put_pixel(fract->img, j, i, get_color(&iter, &fract->max_iter));
            j++;
        }
        i++;
    }
    printf("FINISHED PRINTING MANDELBROT SET\n");
}
