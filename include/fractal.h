/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:27:56 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 12:10:42 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include "../lib/libft/libft.h"
# include "keys.h"

# define WINDOWS_MAX	2

enum			e_union_argb
{
	B, G, R, A
};

enum			e_fractal
{
	MANDEL, JULIA, SHIP, NEWTON, NB_FRACTAL
};

typedef union	u_color
{
	unsigned char	argb[4];
	unsigned int	color;
}				t_color;

enum			e_key_pressed
{
	P_W, P_S, P_D, P_A, P_UP, P_DOWN, P_RIGHT, P_LEFT, NB_KEY_PRESSED
};

typedef struct	s_img
{
	void	*img;
	char	*data;
	int		width;
	int		height;
	int		byte_per_pixel;
	int		line_size;
	int		endian;
}				t_img;

typedef struct	s_vec2f
{
	double	x;
	double	y;
}				t_vec2f;

typedef struct	s_fspace
{
	double		size;
	double		speed;
	t_vec2f		center;
	t_vec2f		pos;
	t_vec2f		interpolat;
	uint		precision;
	double		param_r;
	double		param_i;
}				t_fspace;

typedef struct	s_fractal
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
	t_img		img;
	t_fspace	space;
	bool		key[NB_KEY_PRESSED];
	bool		display_mode;
	uint		idx_fractal;
	t_vec2f		mouse;
}				t_fractal;

bool	init(t_fractal *frac, uint nb);
void	free_fractal(t_fractal *frac);
void	free_all(t_fractal *frac);
int		get_fractal_color(t_fractal *frac);
int		display(t_fractal *frac);
void	exec_event(t_fractal *frac);
int		key_press(int key, t_fractal *frac);
int		key_released(int key, t_fractal *frac);
int		quit_fractal(t_fractal *fractal);
int		mouse_event(int x, int y, t_fractal *frac);

/*
**	fractal
*/

bool	julia(t_fspace *space, double x, double y, double *color);
bool	mandelbrot(t_fspace *space, double x, double y, double *color);
bool	ship(t_fspace *space, double x, double y, double *color);
bool	newton(t_fspace *space, double x, double y, double *color);

bool	(* const g_fractal[NB_FRACTAL])
(t_fspace *space, double x, double y, double *color);

#endif
