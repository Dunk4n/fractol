/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:27:53 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 11:50:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	((int*)img->data)[y * img->line_size + x] = color;
}

void	display_fractal(t_fractal *frac)
{
	int			i;
	int			j;

	exec_event(frac);
	frac->space.interpolat.x = (frac->space.size * 2.0) / (double)frac->width;
	frac->space.interpolat.y = -(frac->space.size * 2.0) / (double)frac->height;
	frac->space.pos.y = frac->space.size + frac->space.center.y;
	i = 0;
	while (i < frac->height)
	{
		frac->space.pos.x = -frac->space.size + frac->space.center.x;
		j = 0;
		while (j < frac->width)
		{
			put_pixel(&frac->img, j, i, get_fractal_color(frac));
			++j;
			frac->space.pos.x += frac->space.interpolat.x;
		}
		frac->space.pos.y += frac->space.interpolat.y;
		++i;
	}
	mlx_put_image_to_window(frac->mlx_ptr, frac->win_ptr, frac->img.img, 0, 0);
}

int		display(t_fractal *frac)
{
	uint	i;
	bool	open;

	i = 0;
	while (i < WINDOWS_MAX)
	{
		if (frac[i].win_ptr)
		{
			display_fractal(frac + i);
		}
		++i;
	}
	i = 0;
	open = false;
	while (i < WINDOWS_MAX)
	{
		if (frac[i++].win_ptr)
		{
			open = true;
			break ;
		}
	}
	if (!open)
		exit(0);
	return (0);
}
