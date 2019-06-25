/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:58:38 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/27 19:58:41 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		main(int ac, char **av)
{
	t_wolf		wolf;
	t_map		map;

	wolf_init(&wolf, av[1]);
	//wolf.file_name = av[1];
	if (!check_norme(&wolf))
		error_exit(MAP_ERR);
	// wolf.map->map = read_map(&wolf);
	// print_map(&wolf);
	return (0);
}

//void	show_map()
