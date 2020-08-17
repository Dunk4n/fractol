/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   burning_ship.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:09:08 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 09:59:57 by niduches         ###   ########.fr       */
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

bool		ship(t_fspace *space, double x, double y, double *color)
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
		{
			*color = i + 1 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
			return (false);
		}
	}
	*color = i + 1 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
	return (true);
}
