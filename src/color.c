/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 12:32:43 by niduches          #+#    #+#             */
/*   Updated: 2020/08/27 13:53:05 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	get_color(t_fractal *frac)
{
	frac->space.color_r_second = rand() % 4 + 1;
	frac->space.color_r_first = (float)(rand() % 100) / 1000;
	frac->space.color_g_second = rand() % 4 + 1;
	frac->space.color_g_first = (float)(rand() % 100) / 1000;
	frac->space.color_b_second = rand() % 4 + 1;
	frac->space.color_b_first = (float)(rand() % 100) / 1000;
}
