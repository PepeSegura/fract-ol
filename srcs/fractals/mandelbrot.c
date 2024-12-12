/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 19:34:16 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/12 10:41:30 by psegura-         ###   ########.fr       */
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
            map_screen_coordinates(i, j, fract);
            iter = mandelbrot(fract->max_iter, &fract->screen[i][j]);
            mlx_put_pixel(fract->img, j, i, get_color(&iter, &fract->max_iter));
            j++;
        }
        i++;
    }
    printf("FINISHED PRINTING MANDELBROT SET\n");
}
