/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_event.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/23 11:12:17 by niduches          #+#    #+#             */
/*   Updated: 2020/09/02 14:32:33 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

static void	exec_event_move(t_fractal *frac)
{
	if (frac->key[P_W] && frac->space.center.y < 2.0)
		frac->space.center.y -= frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_S] && frac->space.center.y > -2.0)
		frac->space.center.y += frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_D] && frac->space.center.x < 2.0)
		frac->space.center.x += frac->space.interpolat.x * frac->space.speed;
	if (frac->key[P_A] && frac->space.center.x > -2.0)
		frac->space.center.x -= frac->space.interpolat.x * frac->space.speed;
}

static void	exec_event_zoom(t_fractal *frac)
{
	if (frac->key[P_UP])
	{
		if (frac->space.center.x < 2.0 && frac->space.center.x > -2.0)
			frac->space.center.x += frac->space.interpolat.x *
			(frac->mouse.x - frac->width / 2) * 0.1;
		if (frac->space.center.y < 2.0 && frac->space.center.y > -2.0)
			frac->space.center.y += frac->space.interpolat.y *
			(frac->mouse.y - frac->height / 2) * 0.1;
		if (frac->space.size - 0.1 * frac->space.size <= 0)
			frac->space.size = 0;
		else
			frac->space.size -= 0.1 * frac->space.size;
	}
	if (!frac->key[P_DOWN])
		return ;
	if (frac->space.center.x < 2.0 && frac->space.center.x > -2.0)
		frac->space.center.x -= frac->space.interpolat.x *
		(frac->mouse.x - frac->width / 2) * 0.1;
	if (frac->space.center.y < 2.0 && frac->space.center.y > -2.0)
		frac->space.center.y -= frac->space.interpolat.y *
		(frac->mouse.y - frac->height / 2) * 0.1;
	if (frac->space.size + 0.1 * frac->space.size >= 4)
		frac->space.size = 4;
	else
		frac->space.size += 0.1 * frac->space.size;
}

void		exec_event(t_fractal *frac)
{
	exec_event_move(frac);
	exec_event_zoom(frac);
	if (frac->key[P_RIGHT])
		frac->space.precision += 1;
	if (frac->key[P_LEFT])
	{
		if (frac->space.precision <= 1)
			frac->space.precision = 0;
		else
			frac->space.precision -= 1;
	}
}
