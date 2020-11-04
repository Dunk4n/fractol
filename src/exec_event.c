/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:12:17 by niduches          #+#    #+#             */
/*   Updated: 2020/11/04 12:45:55 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	exec_event_move(t_fractal *frac)
{
	if (frac->key[P_UP] && frac->space.center.y < 2.0)
		frac->space.center.y -= frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_DOWN] && frac->space.center.y > -2.0)
		frac->space.center.y += frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_RIGHT] && frac->space.center.x < 2.0)
		frac->space.center.x += frac->space.interpolat.x * frac->space.speed;
	if (frac->key[P_LEFT] && frac->space.center.x > -2.0)
		frac->space.center.x -= frac->space.interpolat.x * frac->space.speed;
}

void		exec_event(t_fractal *frac)
{
	exec_event_move(frac);
	if (frac->key[P_W] && frac->space.precision < 4000)
		frac->space.precision += 1;
	if (frac->key[P_S])
	{
		if (frac->space.precision <= 1)
			frac->space.precision = 0;
		else
			frac->space.precision -= 1;
	}
}
