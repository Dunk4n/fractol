/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:50:13 by niduches          #+#    #+#             */
/*   Updated: 2020/08/24 11:54:47 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "fractal.h"

bool	init_thread(t_fractal *frac)
{
	int	i;

	if (pthread_mutex_init(&frac->mutex_work, NULL))
		return (false);
	frac->mutex_init = true;
	sem_unlink("fractol_sem_work");
	sem_unlink("fractol_sem_end");
	if ((frac->sem_work =
sem_open("fractol_sem_work", O_CREAT, 0644, 0)) == SEM_FAILED)
		return (false);
	if ((frac->sem_end =
sem_open("fractol_sem_end", O_CREAT, 0644, 0)) == SEM_FAILED)
		return (false);
	i = 0;
	while (i < NB_THREAD)
	{
		frac->threads[i].fractal = frac;
		if (pthread_create(&frac->threads[i].thread, NULL, worcker,
frac->threads + i) == -1)
			return (false);
		frac->threads[i].created = true;
		++i;
	}
	return (true);
}

void	free_fractal_thread(t_fractal *frac)
{
	uint	i;

	frac->end = true;
	i = 0;
	while (frac->sem_work != SEM_FAILED && i < NB_THREAD)
	{
		sem_post(frac->sem_work);
		++i;
	}
	i = 0;
	while (i < NB_THREAD)
	{
		if (frac->threads[i].created)
		{
			pthread_join(frac->threads[i].thread, NULL);
			pthread_detach(frac->threads[i].thread);
		}
		++i;
	}
	sem_close(frac->sem_work);
	sem_close(frac->sem_end);
	sem_unlink("fractol_sem_work");
	sem_unlink("fractol_sem_end");
	if (frac->mutex_init)
		pthread_mutex_destroy(&frac->mutex_work);
}
