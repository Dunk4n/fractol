/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:09:12 by niduches          #+#    #+#             */
/*   Updated: 2020/11/04 13:16:15 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <X11/Xlib.h>
#include "fractal.h"

int			quit_fractal(t_fractal *fractal)
{
	free_fractal(fractal);
	return (0);
}

static void	display_msg(t_fractal *fractal)
{
	uint	i;
	char	*fractal_name[NB_FRACTAL];

	fractal_name[MANDEL] = "mandelbrot";
	fractal_name[JULIA] = "julia";
	fractal_name[SHIP] = "ship";
	fractal_name[NEWTON] = "newton";
	fractal_name[JULIA4] = "julia4";
	fractal_name[JULIA1] = "julia1";
	i = 0;
	while (i < NB_FRACTAL)
	{
		ft_putstr_fd(fractal_name[i], 1);
		ft_putchar_fd('\n', 1);
		++i;
	}
	free_all(fractal);
	exit(0);
}

void		set_idx_fractals(uint ac, char **av, t_fractal *frac)
{
	uint	i;
	uint	j;
	char	*fractal_name[NB_FRACTAL];

	fractal_name[MANDEL] = "mandelbrot";
	fractal_name[JULIA] = "julia";
	fractal_name[SHIP] = "ship";
	fractal_name[NEWTON] = "newton";
	fractal_name[JULIA4] = "julia4";
	fractal_name[JULIA1] = "julia1";
	i = 0;
	while (i++ < ac)
	{
		j = 0;
		while (j < NB_FRACTAL)
		{
			if (!ft_strcmp(av[i - 1], fractal_name[j]))
			{
				frac[i - 1].idx_fractal = j;
				break ;
			}
			if (++j >= NB_FRACTAL)
				display_msg(frac);
		}
	}
}

static void	init_event(t_fractal *frac, uint nb)
{
	uint		i;

	i = 0;
	while (i < nb)
	{
		mlx_hook(frac[i].win_ptr, DestroyNotify, StructureNotifyMask,
		quit_fractal, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, KeyPress, KeyPressMask,
		key_press, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, KeyRelease, KeyReleaseMask,
		key_released, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, MotionNotify, PointerMotionMask,
		mouse_event, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, ButtonPress, ButtonPressMask,
		mouse_weel, (void*)(&frac[i]));
		++i;
	}
	mlx_loop_hook(frac->mlx_ptr, display, (void*)(frac));
}

int			main(int ac, char **av)
{
	t_fractal	frac[WINDOWS_MAX];
	uint		nb;

	srand(time(NULL));
	if (ac - 1 > WINDOWS_MAX)
		return (0);
	nb = ac - 1;
	if (!init(frac, nb))
		return (0);
	if (nb == 0)
		display_msg(frac);
	set_idx_fractals(ac - 1, av + 1, frac);
	init_event(frac, nb);
	mlx_loop(frac->mlx_ptr);
	return (0);
}
