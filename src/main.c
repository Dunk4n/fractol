/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: niduches <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 15:09:12 by niduches          #+#    #+#             */
/*   Updated: 2020/08/17 12:04:28 by niduches         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractal.h"

bool	(* const g_fractal[NB_FRACTAL])
(t_fspace *space, double x, double y, double *color) =
{
	mandelbrot, julia, ship, newton,
};

const char	*g_fractal_name[NB_FRACTAL] =
{
	"mandelbrot", "julia", "ship", "newton",
};

int		quit_fractal(t_fractal *fractal)
{
	free_fractal(fractal);
	return (0);
}

void	display_msg(t_fractal *fractal)
{
	uint	i;

	i = 0;
	while (i < NB_FRACTAL)
	{
		ft_putstr_fd((char*)g_fractal_name[i], 1);
		ft_putchar_fd('\n', 1);
		++i;
	}
	free_all(fractal);
	exit(0);
}

void	set_idx_fractals(uint ac, char **av, t_fractal *frac)
{
	uint	i;
	uint	j;

	i = 0;
	while (i < ac)
	{
		j = 0;
		while (j < NB_FRACTAL)
		{
			if (!ft_strcmp(av[i], g_fractal_name[j]))
			{
				frac[i].idx_fractal = j;
				break ;
			}
			++j;
			if (j >= NB_FRACTAL)
				display_msg(frac);
		}
		++i;
	}
}

int		main(int ac, char **av)
{
	t_fractal	frac[WINDOWS_MAX];
	uint		i;
	uint		nb;

	if (ac - 1 > WINDOWS_MAX)
		return (0);
	nb = ac - 1;
	if (!init(frac, nb))
		return (0);
	if (nb == 0)
		display_msg(frac);
	set_idx_fractals(ac - 1, av + 1, frac);
	i = 0;
	while (i < nb)
	{
		mlx_hook(frac[i].win_ptr, 17, 0L, quit_fractal, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, 2, 1L << 0, key_press, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, 3, 1L << 1, key_released, (void*)(&frac[i]));
		mlx_hook(frac[i].win_ptr, 6, 0x40L, mouse_event, (void*)(&frac[i]));
		++i;
	}
	mlx_loop_hook(frac->mlx_ptr, display, (void*)(frac));
	mlx_loop(frac->mlx_ptr);
	return (0);
}
