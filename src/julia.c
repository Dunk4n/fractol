/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 17:48:38 by niduches          #+#    #+#             */
/*   Updated: 2020/11/04 13:15:21 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static int	color_julia(t_fspace *space, uint nb, bool find)
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

int			julia4(t_fspace *space, double x, double y)
{
	double	res;
	double	resi;
	double	tmp;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		tmp = res * res - resi * resi + 0.25;
		resi = 2 * res * resi;
		res = tmp;
		++i;
		if (res * res + resi * resi >= 4)
			return (color_julia(space, i, false));
	}
	return (color_julia(space, i, true));
}

int			julia1(t_fspace *space, double x, double y)
{
	double	res;
	double	resi;
	double	tmp;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		tmp = res * res - resi * resi - 1;
		resi = 2 * res * resi;
		res = tmp;
		++i;
		if (res * res + resi * resi >= 4)
			return (color_julia(space, i, false));
	}
	return (color_julia(space, i, true));
}

int			julia(t_fspace *space, double x, double y)
{
	double	res;
	double	resi;
	double	tmp;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		tmp = res * res - resi * resi + space->param_r;
		resi = 2 * res * resi + space->param_i;
		res = tmp;
		++i;
		if (res * res + resi * resi >= 4)
			return (color_julia(space, i, false));
	}
	return (color_julia(space, i, true));
}
