/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractal.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 11:50:16 by niduches          #+#    #+#             */
/*   Updated: 2020/08/27 14:06:13 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

int		get_fractal_color(t_fractal *frac, double x, double y)
{
	return (g_fractal[frac->idx_fractal](&frac->space, x, y));
}
