/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   newton.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 18:22:26 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 10:00:33 by niduches         ###   ########.fr       */
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

bool			newton(t_fspace *space, double x, double y, double *color)
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
		{
			++i;
			*color = i + 1 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
			return (false);
		}
		++i;
	}
	*color = i + 1 - (log(2) / sqrt(res * res + resi * resi)) / log(2);
	return (true);
}
