/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 22:34:57 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/09 16:15:59 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

inline bool	set_zoom_and_offsets(double scale, t_fractol *fractol)
{
	if (scale == 0.0)
		return (false);
	fractol->cursor.real = (fractol->cursor_pos.x - SCREEN_WIDTH / 2.0) / (SCREEN_WIDTH / 2.0) * fractol->zoom + fractol->offset_x;
	fractol->cursor.imag = (fractol->cursor_pos.y - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0) * fractol->zoom + fractol->offset_y;
	printf("zoom from point (%d,%d)\n", fractol->cursor_pos.x, fractol->cursor_pos.y);
	fractol->zoom *= scale;
	fractol->offset_x = fractol->cursor.real - (fractol->cursor_pos.x - SCREEN_WIDTH / 2.0) / (SCREEN_WIDTH / 2.0) * fractol->zoom;
	fractol->offset_y = fractol->cursor.imag - (fractol->cursor_pos.y - SCREEN_HEIGHT / 2.0) / (SCREEN_HEIGHT / 2.0) * fractol->zoom;
	return (true);
}

void	my_scrollhook(double xdelta, double ydelta, void *param)
{
	t_fractol	*fractol;
	double		zoom;

	(void)xdelta;
	fractol = (t_fractol *)param;
	zoom = 0.0;
	if (ydelta == -1)
		zoom = 1.1;
	else if (ydelta == 1)
		zoom = 0.9;
	if (set_zoom_and_offsets(zoom, fractol) == true)
		draw_fractal(fractol);
}

void	my_cursorhook(double xpos, double ypos, void *param)
{
	((t_fractol *)param)->cursor_pos.x = xpos;
	((t_fractol *)param)->cursor_pos.y = ypos;
}

void	my_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fractol	*fractol;
	int			paint;
	const int	prev = ((t_fractol *)param)->max_iter;

	paint = 0;
	fractol = (t_fractol *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		printf("Escape!\n");
		mlx_terminate(fractol->mlx);
		exit(1);
	}
	else if (keydata.key == MLX_KEY_R && keydata.action == MLX_PRESS)
	{
		reset_fractol(fractol);
		paint = 1;
	}
	else if (keydata.key == MLX_KEY_UP && keydata.action == MLX_PRESS)
	{
		if ((fractol->max_iter * 1.1) > 2000.0)
		{
			printf("To many iterations!!\n");
			return ;
		}
		paint = 1;
		fractol->max_iter *= 1.1;
		printf("Increment Iterations %d -> %f\n", prev, fractol->max_iter);
	}
	else if (keydata.key == MLX_KEY_DOWN && keydata.action == MLX_PRESS)
	{
		if ((fractol->max_iter *= 0.9) < 2)
		{
			printf("To few iterations!!\n");
			return ;
		}
		paint = 1;
		fractol->max_iter *= 0.9;
		printf("Decrement Iterations %d -> %f\n", prev, fractol->max_iter);
	}
	if (paint)
		draw_fractal(fractol);
}
