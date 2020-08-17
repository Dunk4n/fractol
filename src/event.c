/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 14:42:28 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 12:19:14 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		key_released(int key, t_fractal *frac)
{
	if (key == K_ESC)
		quit_fractal(frac);
	if (key == K_O)
		frac->idx_fractal = (frac->idx_fractal + 1) % NB_FRACTAL;
	if (key == K_P)
		frac->display_mode = !frac->display_mode;
	if (key == K_W)
		frac->key[P_W] = false;
	if (key == K_S)
		frac->key[P_S] = false;
	if (key == K_D)
		frac->key[P_D] = false;
	if (key == K_A)
		frac->key[P_A] = false;
	if (key == K_UP)
		frac->key[P_UP] = false;
	if (key == K_DOWN)
		frac->key[P_DOWN] = false;
	if (key == K_RIGHT)
		frac->key[P_RIGHT] = false;
	if (key == K_LEFT)
		frac->key[P_LEFT] = false;
	return (0);
}

int		key_press(int key, t_fractal *frac)
{
	if (key == K_W)
		frac->key[P_W] = true;
	if (key == K_S)
		frac->key[P_S] = true;
	if (key == K_D)
		frac->key[P_D] = true;
	if (key == K_A)
		frac->key[P_A] = true;
	if (key == K_UP)
		frac->key[P_UP] = true;
	if (key == K_DOWN)
		frac->key[P_DOWN] = true;
	if (key == K_RIGHT)
		frac->key[P_RIGHT] = true;
	if (key == K_LEFT)
		frac->key[P_LEFT] = true;
	return (0);
}

void	exec_event(t_fractal *frac)
{
	if (frac->key[P_W] && frac->space.center.y < 2.0)
		frac->space.center.y -= frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_S] && frac->space.center.y > -2.0)
		frac->space.center.y += frac->space.interpolat.y * frac->space.speed;
	if (frac->key[P_D] && frac->space.center.x < 2.0)
		frac->space.center.x += frac->space.interpolat.x * frac->space.speed;
	if (frac->key[P_A] && frac->space.center.x > -2.0)
		frac->space.center.x -= frac->space.interpolat.x * frac->space.speed;
	if (frac->key[P_UP])
	{
		if (frac->space.center.x < 2.0 && frac->space.center.x > -2.0)
			frac->space.center.x += frac->space.interpolat.x * (frac->mouse.x - frac->width / 2) * 0.1;
		if (frac->space.center.y < 2.0 && frac->space.center.y > -2.0)
			frac->space.center.y += frac->space.interpolat.y * (frac->mouse.y - frac->height / 2) * 0.1;
		if (frac->space.size - 0.1 * frac->space.size <= 0)
			frac->space.size = 0;
		else
			frac->space.size -= 0.1 * frac->space.size;
	}
	if (frac->key[P_DOWN])
	{
		if (frac->space.center.x < 2.0 && frac->space.center.x > -2.0)
			frac->space.center.x -= frac->space.interpolat.x * (frac->mouse.x - frac->width / 2) * 0.1;
		if (frac->space.center.y < 2.0 && frac->space.center.y > -2.0)
			frac->space.center.y -= frac->space.interpolat.y * (frac->mouse.y - frac->height / 2) * 0.1;
		if (frac->space.size + 0.1 * frac->space.size >= 4)
			frac->space.size = 4;
		else
			frac->space.size += 0.1 * frac->space.size;
	}
	if (frac->key[P_RIGHT])
		frac->space.precision += 5;
	if (frac->key[P_LEFT])
	{
		if (frac->space.precision < 5)
			frac->space.precision = 1;
		else
			frac->space.precision -= 5;
	}
}

int		mouse_event(int x, int y, t_fractal *frac)
{
	frac->mouse.x = x;
	frac->mouse.y = y;
	frac->space.param_r = (double)(x - frac->width / 2) / 500.0;
	frac->space.param_i = (double)(y - frac->height / 2) / 500.0;
	return (0);
}
