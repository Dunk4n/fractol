/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/18 11:42:29 by niduches          #+#    #+#             */
/*   Updated: 2020/08/18 15:39:50 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

void	put_pixel(t_img *img, int x, int y, int color)
{
	((int*)img->data)[y * img->line_size + x] = color;
}

void	take_work(t_thread *thread)
{
	pthread_mutex_lock(&thread->fractal->mutex_work);
	if (thread->fractal->work_start < thread->fractal->height)
	{
		thread->start = thread->fractal->work_start;
		thread->fractal->work_start += NB_LINE_WORK;
	}
	else
		thread->start = thread->fractal->height;
	pthread_mutex_unlock(&thread->fractal->mutex_work);
}

void	do_work(t_thread *thread)
{
	int			i;
	int			j;
	double		y;
	double		x;

	y = thread->fractal->space.size + thread->fractal->space.center.y +
((double)thread->start * thread->fractal->space.interpolat.y);
	i = 0;
	while (i < NB_LINE_WORK)
	{
		x = -thread->fractal->space.size + thread->fractal->space.center.x;
		j = 0;
		while (j < thread->fractal->width)
		{
			put_pixel(&thread->fractal->img, j, i + thread->start,
			get_fractal_color(thread->fractal, x, y));
			++j;
			x += thread->fractal->space.interpolat.x;
		}
		y += thread->fractal->space.interpolat.y;
		++i;
	}
}

void	*worcker(void *data)
{
	t_thread	*thread;

	thread = (t_thread*)data;
	while (!thread->fractal->end)
	{
		sem_wait(thread->fractal->sem_work);
		if (thread->fractal->end)
		{
			sem_post(thread->fractal->sem_end);
			return ((void*)0);
		}
		take_work(thread);
		if (thread->fractal->end)
		{
			sem_post(thread->fractal->sem_end);
			return ((void*)0);
		}
		if (thread->start < thread->fractal->height)
			do_work(thread);
		sem_post(thread->fractal->sem_end);
	}
	return ((void*)0);
}
