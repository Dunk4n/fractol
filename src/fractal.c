/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:50:16 by niduches          #+#    #+#             */
/*   Updated: 2020/11/04 13:04:38 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		get_fractal_color(t_fractal *frac, double x, double y)
{
	int		(*fractal[NB_FRACTAL])(t_fspace *space, double x, double y);

	fractal[MANDEL] = mandelbrot;
	fractal[JULIA] = julia;
	fractal[SHIP] = ship;
	fractal[NEWTON] = newton;
	fractal[JULIA4] = julia4;
	fractal[JULIA1] = julia1;
	return (fractal[frac->idx_fractal](&frac->space, x, y));
}
