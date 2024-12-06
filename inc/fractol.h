#ifndef FDF_H
# define FDF_H

# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <string.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "MLX42/MLX42.h"

# define DEFAULT_COLOR 0xFF0000FF

# define BPP sizeof(int32_t)

# define SCREEN_WIDTH 500
# define SCREEN_HEIGHT 500

# define PI		3.14
# define PI2	6.18
# define PI05	1.57
# define PI025	0.78

typedef struct s_camera
{
	int			offsets[2];
	int			key_offset[2];
	double		scale;
	double		initial_scale;

	// TEST
	double		x_deg;
	double		y_deg;
	double		z_deg;
	double		depth_change;
	// TEST
}	t_camera;

typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

/* t_complex.c */
t_complex	add(t_complex a, t_complex b);
t_complex	substract(t_complex a, t_complex b);
t_complex	mult(t_complex a, t_complex b);
t_complex	division(t_complex a, t_complex b);
double		magnitude(t_complex a);
void		printComplex(t_complex a);

typedef struct s_point
{
	int	x;
	int	y;
}	t_point;

typedef struct s_fractol
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_point		cursor_pos;
	t_complex	cursor;
	t_complex	screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	int			max_iter;
	double		zoom;
	double		offset_x;
	double		offset_y;
}   t_fractol;

void	reset_fractol(t_fractol *fractol);

/* parse_input.c */
void	parse_input(int argc, char **argv, t_fractol *fractol);


/* mlx_tools.c */
int get_rgba(int r, int g, int b, int a);
int get_r(int rgba);
int get_g(int rgba);
int get_b(int rgba);
int get_a(int rgba);


/* hooks.c */
void    my_key_hook(mlx_key_data_t keydata, void* param);
void	my_scrollhook(double xdelta, double ydelta, void *param);
void    my_cursorhook(double xpos, double ypos, void* param);


/* errors.c */
void	ft_perror(char *msg);
void	ft_error(char *str);

/* mandelbrot.c */
void    draw_mandelbrot(t_fractol *fractol);

#endif
