/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 10:26:18 by niduches          #+#    #+#             */
/*   Updated: 2020/09/02 14:35:02 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	next_step(t_fractal_calc *calc, double x, double y)
{
	calc->tmpi = (calc->tmp + calc->tmp) * calc->tmpi + y;
	calc->tmp = calc->res - calc->resi + x;
	calc->res = calc->tmp * calc->tmp;
	calc->resi = calc->tmpi * calc->tmpi;
}

static bool	mandelbrot_is_in_opti(t_fspace *space, t_fractal_calc *calc, uint i)
{
	return (i > 1 && ((calc->res - calc->tres < 0.005 * space->size &&
calc->res - calc->tres > -0.005 * space->size && calc->resi - calc->tresi <
0.005 * space->size && calc->resi - calc->tresi > -0.005 * space->size) ||
(calc->res - calc->lres < 0.001 * space->size && calc->res - calc->lres >
-0.001 * space->size && calc->resi - calc->lresi < 0.001 * space->size &&
calc->resi - calc->lresi > -0.001 * space->size)));
}

static void	mandelbrot_set_opti(t_fractal_calc *calc, uint i)
{
	calc->tres = calc->res;
	calc->tresi = calc->resi;
	if (i == 0 || calc->res < calc->tres || calc->resi < calc->tresi)
	{
		calc->lres = calc->res;
		calc->lresi = calc->resi;
	}
}

static int	color_mandelbrot(t_fspace *space, uint nb, bool find)
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

int			mandelbrot(t_fspace *space, double x, double y)
{
	t_fractal_calc	calc;
	uint			i;

	i = 0;
	calc.resi = 0;
	calc.res = 0;
	calc.tmp = 0;
	calc.tmpi = 0;
	calc.tresi = 0;
	calc.tres = 0;
	calc.lresi = 0;
	calc.lres = 0;
	while (i < space->precision)
	{
		next_step(&calc, x, y);
		if (mandelbrot_is_in_opti(space, &calc, i))
			return (color_mandelbrot(space, i, true));
		mandelbrot_set_opti(&calc, i);
		if (calc.res + calc.resi >= 4.0)
			return (color_mandelbrot(space, i, false));
		++i;
	}
	return (color_mandelbrot(space, i, true));
}
