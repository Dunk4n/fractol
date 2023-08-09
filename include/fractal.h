/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:27:56 by niduches          #+#    #+#             */
/*   Updated: 2020/11/12 20:53:47 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTAL_H
# define FRACTAL_H

# include <stdbool.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <semaphore.h>
# include "../lib/libft/libft.h"
# include "keys.h"

# define WINDOWS_MAX	3
# define NB_THREAD	10
# define NB_LINE_WORK 1
# define START_PRECISION 100

enum			e_union_argb
{
	B, G, R, A
};

enum			e_fractal
{
	MANDEL, JULIA, SHIP, NEWTON, JULIA4, JULIA1, NB_FRACTAL
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

typedef struct	s_fractal_calc
{
	double	res;
	double	resi;
	double	tres;
	double	tresi;
	double	lres;
	double	lresi;
	double	tmp;
	double	tmpi;
}				t_fractal_calc;

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
	float		color_r_first;
	float		color_g_first;
	float		color_b_first;
	int			color_r_second;
	int			color_g_second;
	int			color_b_second;
	bool		display_mode;
}				t_fspace;

struct s_fractal;

typedef struct	s_thread
{
	bool				created;
	pthread_t			thread;
	struct s_fractal	*fractal;
	int					start;
}				t_thread;

typedef struct	s_fractal
{
	void			*mlx_ptr;
	void			*win_ptr;
	int				width;
	int				height;
	t_img			img;
	t_fspace		space;
	bool			key[NB_KEY_PRESSED];
	bool			init;
	uint			idx_fractal;
	t_vec2f			mouse;
	int				work_start;
	bool			end;
	bool			mutex_init;
	t_thread		threads[NB_THREAD];
	pthread_mutex_t	mutex_work;
	sem_t			*sem_work;
	sem_t			*sem_end;
}				t_fractal;

bool			init(t_fractal *frac, uint nb);
void			free_fractal(t_fractal *frac);
void			free_all(t_fractal *frac);
int				get_fractal_color(t_fractal *frac, double x, double y);
int				display(t_fractal *frac);
void			exec_event(t_fractal *frac);
int				key_press(int key, t_fractal *frac);
int				key_released(int key, t_fractal *frac);
int				quit_fractal(t_fractal *fractal);
int				mouse_event(int x, int y, t_fractal *frac);
void			get_color(t_fractal *frac);
bool			init_thread(t_fractal *frac);
void			*worcker(void *thread);
void			free_fractal_thread(t_fractal *frac);
t_vec2f			c_add(t_vec2f a, t_vec2f b);
t_vec2f			c_sub(t_vec2f a, t_vec2f b);
t_vec2f			c_mult(t_vec2f a, t_vec2f b);
int				mouse_weel(int button, int x, int y, t_fractal *frac);

/*
**	fractal
*/

int				julia(t_fspace *space, double x, double y);
int				julia4(t_fspace *space, double x, double y);
int				julia1(t_fspace *space, double x, double y);
int				mandelbrot(t_fspace *space, double x, double y);
int				ship(t_fspace *space, double x, double y);
int				newton(t_fspace *space, double x, double y);

#endif
