/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:22:26 by niduches          #+#    #+#             */
/*   Updated: 2020/08/27 14:09:34 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static double	next_step(double *res, double *resi)
{
	double	old;
	double	oldi;
	double	tmp;

	old = *res;
	oldi = *resi;
	tmp = (*res * *res + *resi * *resi) * (*res * *res + *resi * *resi);
	*res = (2 * *res * tmp + *res * *res - *resi * *resi) / (3.0 * tmp);
	*resi = (2 * *resi * (tmp - old)) / (3.0 * tmp);
	return ((*res - old) * (*res - old) + (*resi - oldi) * (*resi - oldi));
}

static int		color_newton(t_fspace *space, uint nb, bool find)
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

int				newton(t_fspace *space, double x, double y)
{
	double	res;
	double	resi;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		if (next_step(&res, &resi) <= 0.000001)
			return (color_newton(space, i, false));
		++i;
	}
	return (color_newton(space, i, true));
}
