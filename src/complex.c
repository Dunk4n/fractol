/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   complex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/27 12:17:58 by niduches          #+#    #+#             */
/*   Updated: 2020/09/02 14:31:07 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

t_vec2f		c_add(t_vec2f a, t_vec2f b)
{
	return ((t_vec2f){a.x + b.x, b.y + a.y});
}

t_vec2f		c_sub(t_vec2f a, t_vec2f b)
{
	return ((t_vec2f){a.x - b.x, b.y - a.y});
}

t_vec2f		c_mult(t_vec2f a, t_vec2f b)
{
	return ((t_vec2f){a.x * b.x - a.y * b.y, a.x * b.y - a.y * b.x});
}
