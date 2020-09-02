/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:09:08 by niduches          #+#    #+#             */
/*   Updated: 2020/09/02 14:33:48 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	next_step(double *res, double *resi,
double x, double y)
{
	double	tmpi;

	tmpi = *resi;
	*resi = fabs((double)(*res * *resi + *res * *resi + y));
	*res = fabs((double)(*res * *res - tmpi * tmpi + x));
}

static int	color_ship(t_fspace *space, uint nb, bool find)
{
	double	idx;
	t_color	col;

	if (!space->display_mode && find)
		return (0);
	idx = nb;
	col.argb[R] = (uint)(sin(space->color_r_first * idx +
(double)space->color_r_second) * 230.0 + 25.0);
	col.argb[G] = (uint)(sin(space->color_g_first * idx +
(double)space->color_g_second) * 230.0 + 25.0);
	col.argb[B] = (uint)(sin(space->color_b_first * idx +
(double)space->color_b_second) * 230.0 + 25.0);
	col.argb[A] = 255;
	return (col.color);
}

int			ship(t_fspace *space, double x, double y)
{
	double	res;
	double	resi;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		next_step(&res, &resi, x, y);
		++i;
		if (res * res + resi * resi >= 4)
			return (color_ship(space, i, false));
	}
	return (color_ship(space, i, true));
}
