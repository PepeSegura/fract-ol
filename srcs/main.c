/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: psegura- <psegura-@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 18:58:58 by psegura-          #+#    #+#             */
/*   Updated: 2024/12/09 13:08:03 by psegura-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

mlx_t    *init_and_customize_mlx(t_fractol *fractol)
{
	(void)fractol;
    mlx_t           *mlx;
    mlx_win_cursor_t *cursor; 

    mlx_set_setting(MLX_DECORATED, false);
    mlx = mlx_init(SCREEN_WIDTH, SCREEN_HEIGHT, "fractol", false);
	if (mlx == NULL)
		ft_error("Can't load mlx", true);
    cursor = mlx_create_std_cursor(MLX_CURSOR_CROSSHAIR);
    mlx_set_cursor(mlx, cursor);
    return (mlx);
}

void	mlx_stuff(t_fractol *fractol)
{
	mlx_t           *mlx;
	mlx_image_t     *img;

    mlx = init_and_customize_mlx(fractol);
	img = mlx_new_image(mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
	if (!img || (mlx_image_to_window(mlx, img, 0, 0) < 0))
		ft_error("Can't load img", true);
	fractol->img = img;
	fractol->mlx = mlx;
	draw_fractal(fractol);
    mlx_key_hook(mlx, my_key_hook, fractol);
	mlx_scroll_hook(mlx, &my_scrollhook, fractol);
	mlx_cursor_hook(mlx, &my_cursorhook, fractol);
	mlx_loop(mlx);
	mlx_terminate(mlx);
}

void	reset_fractol(t_fractol *fractol)
{
	fractol->max_iter = 200;
	fractol->offset_x = 0;
	fractol->offset_y = 0;
	fractol->zoom = 1;
}

void	parse_input(int argc, char **argv, t_fractol *fractol)
{
	(void)argc, (void)argv, (void)fractol;
	if (argc == 1)
		ft_error("./fractol mandelbrot\n\t./fractol julia", false);
	if (argc == 2 && ft_strcmp(argv[1], "mandelbrot") == 0)
	{
		printf("Using MANDELBROT\n");
		fractol->mode = MANDELBROT;
	}
	else if (argc == 4 && ft_strcmp(argv[1], "julia") == 0)
	{
		printf("Using JULIA\n");
		fractol->mode = JULIA;
		fractol->julia.real = ft_atod(argv[2]);
		fractol->julia.imag = ft_atod(argv[3]);
		// exit(0);
	}
	else
		ft_error("./fractol mandelbrot\n\t./fractol julia", true);
}

int	main(int argc, char **argv)
{
	(void)argc, (void)argv;
	t_fractol	fractol;

	ft_bzero(&fractol, sizeof(fractol));
	parse_input(argc, argv, &fractol);
	reset_fractol(&fractol);
	mlx_stuff(&fractol);
	exit(EXIT_SUCCESS);
}
