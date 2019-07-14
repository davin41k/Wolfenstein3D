/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:18:53 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/27 18:18:55 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		escape_exit(int key, t_wolf *wolf)
{
	(void)wolf;
	if (key == 53)
	{
		exit(0);
	}
	return (0);
}

int		red_exit(int key, t_wolf *wolf)
{
	(void)key;
	(void)wolf;
	exit(0);
	return (0);
}

void	read_error(void)
{
	ft_putendl("a map read error");
	exit(0);
}

void	error_exit(int errno)
{
	if (errno == USAGE)
	{
		ft_putendl("usage:    ./fractol a_number:");
		ft_putendl("1 - Mandelbrot, 2 - Julia, 3 - Burning Ship");
	}
	else if (errno == THREAD_ERR)
		ft_putendl("thread error");
	else if (errno == MEM_ERR)
		ft_putendl("memory error");
	else if (errno == MAP_ERR)
		ft_putendl("error: map is not correct");
	else if (errno == INCORRECT_MAP)
		ft_putendl("error: map is too big or too long");
	else if (errno == LOAD_ERR)
		ft_putendl("error: textures was not load");
	exit(0);
}
