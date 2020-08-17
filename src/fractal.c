/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:50:16 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 10:00:17 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		get_fractal_color(t_fractal *frac)
{
	double	idx;

	if (frac->display_mode)
	{
		g_fractal[frac->idx_fractal]
		(&frac->space, frac->space.pos.x, frac->space.pos.y, &idx);
	}
	else
	{
		if (g_fractal[frac->idx_fractal]
		(&frac->space, frac->space.pos.x, frac->space.pos.y, &idx))
			return (0);
	}
	t_color	col;

	col.argb[R] = (uint)(sin(0.016 * idx + 4) * 230 + 25);
	col.argb[G] = (uint)(sin(0.013 * idx + 2) * 230 + 25);
	col.argb[B] = (uint)(sin(0.01 * idx + 1) * 230 + 25);
	col.argb[A] = 255;
	return (col.color);
}
