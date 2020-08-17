/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:30:14 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 11:08:43 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	init_space(t_fspace *space, t_fractal *frac)
{
	uint	i;

	i = 0;
	while (i < NB_KEY_PRESSED)
		frac->key[i++] = false;
	frac->display_mode = false;
	space->size = 2;
	space->speed = 10;
	space->center.x = 0;
	space->center.y = 0;
	space->pos.x = 0;
	space->pos.y = 0;
	space->interpolat.x = 0;
	space->interpolat.y = 0;
	space->precision = 100;
	space->param_r = 0;
	space->param_i = 0;
}

bool	init_fractal(t_fractal *frac, void *mlx_ptr)
{
	frac->mlx_ptr = mlx_ptr;
	init_space(&frac->space, frac);
	frac->idx_fractal = 0;
	frac->win_ptr = NULL;
	frac->img.img = NULL;
	frac->width = 600;
	frac->height = 600;
	if (!(frac->win_ptr =
mlx_new_window(frac->mlx_ptr, frac->width, frac->height, "fractol")))
		return (false);
	if (!(frac->img.img =
mlx_new_image(frac->mlx_ptr, frac->width, frac->height)))
		return (false);
	frac->img.data = mlx_get_data_addr(frac->img.img,
&frac->img.byte_per_pixel, &frac->img.line_size, &frac->img.endian);
	frac->img.line_size /= 4;
	frac->img.width = frac->width;
	frac->img.height = frac->height;
	return (true);
}

bool	init(t_fractal *frac, uint nb)
{
	void	*mlx_ptr;
	uint	i;

	if (!(mlx_ptr = mlx_init()))
		return (false);
	i = 0;
	while (i < WINDOWS_MAX)
	{
		frac[i].win_ptr = NULL;
		frac[i].img.img = NULL;
		++i;
	}
	i = 0;
	while (i < nb)
	{
		if (!init_fractal(&frac[i], mlx_ptr))
		{
			free_all(frac);
			return (false);
		}
		++i;
	}
	return (true);
}

void	free_fractal(t_fractal *frac)
{
	if (frac->win_ptr)
	{
		mlx_destroy_window(frac->mlx_ptr, frac->win_ptr);
		frac->win_ptr = NULL;
	}
	if (frac->img.img)
	{
		mlx_destroy_image(frac->mlx_ptr, frac->img.img);
		frac->img.img = NULL;
	}
}

void	free_all(t_fractal *frac)
{
	uint	i;

	i = 0;
	while (i < WINDOWS_MAX)
	{
		free_fractal(&frac[i]);
		++i;
	}
}
