/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   julia.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 17:48:38 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 10:00:25 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	next_step(double *res, double *resi,
double x, double y)
{
	double	tmp;
	double	tmpi;

	tmp = *res;
	tmpi = *resi;
	*res = (tmp * tmp) - (tmpi * tmpi) + x;
	*resi = 2 * (tmp * tmpi) + y;
}

bool		mandelbrot(t_fspace *space, double x, double y, double *color)
{
	double	res;
	double	resi;
//	double	tres;
//	double	tresi;
//	double	lres;
//	double	lresi;
	uint	i;

	i = 0;
	resi = 0;
	res = 0;
//	tresi = 0;
//	tres = 0;
//	lresi = 0;
//	lres = 0;
	while (i < space->precision)
	{
		next_step(&res, &resi, x, y);
//		if (i > 1 && ((res - tres < 0.05 && res - tres > -0.05 &&
//resi - tresi < 0.05 && resi - tresi > -0.05) ||
//(res - lres < 0.01 && res - lres > -0.01 &&
//resi - lresi < 0.01 && resi - lresi > -0.01 && i > 50)))
//			return (true);
//		tres = res;
//		tresi = resi;
//		if (i == 0 || res < tres || resi < tresi)
//		{
//			lres = res;
//			lresi = resi;
//		}
		++i;
		if (res * res + resi * resi >= 4)
		{
			*color = (double)i + 1.0 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
			return (false);
		}
	}
	*color = (double)i + 1.0 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
	return (true);
}

bool		julia(t_fspace *space, double x, double y, double *color)
{
	double	res;
	double	resi;
	uint	i;

	i = 0;
	resi = y;
	res = x;
	while (i < space->precision)
	{
		next_step(&res, &resi, space->param_r, space->param_i);
		++i;
		if (res * res + resi * resi >= 4)
		{
			*color = (double)i + 1. - (log(2) / sqrt(res * res + resi * resi)) / log(2);
			return (false);
		}
	}
	*color = (double)i + 1.0 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
	return (true);
}
