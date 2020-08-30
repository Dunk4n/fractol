/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:27:53 by niduches          #+#    #+#             */
/*   Updated: 2020/08/27 15:14:13 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	display_fractal(t_fractal *frac)
{
	uint	i;
	uint	nb_work;

	exec_event(frac);
	frac->space.interpolat.x = (frac->space.size * 2.0) / (double)frac->width;
	frac->space.interpolat.y = -(frac->space.size * 2.0) / (double)frac->height;
	frac->space.pos.y = frac->space.size + frac->space.center.y;
	nb_work = ((double)frac->height / (double)NB_LINE_WORK) + 0.5;
	frac->work_start = 0;
	i = 0;
	while (i < nb_work)
	{
		sem_post(frac->sem_work);
		++i;
	}
	i = 0;
	while (i < nb_work)
	{
		sem_wait(frac->sem_end);
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
			display_fractal(frac + i);
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
