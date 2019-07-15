/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/10 14:30:21 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/10 14:30:22 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static	int		*find_empty_place(t_wolf *wolf)
{
	int		**map;
	int		*empty_place;
	int		i;
	int		j;

	map = wolf->map->map;
	empty_place = (int*)ft_memalloc(sizeof(int) * 2);
	i = -1;
	while (++i < get_count_y(GET_NUM))
	{
		j = -1;
		while (++j < get_count_x(GET_NUM))
		{
			if (map[i][j] == 0)
			{
				empty_place[0] = i;
				empty_place[i] = j;
				return (empty_place);
			}
		}
	}
	return (NULL);
}

void			plant_player(t_wolf *wolf)
{
	int		*empty_place;

	empty_place = find_empty_place(wolf);
	if (empty_place == NULL)
		error_exit(MAP_ERR);
	wolf->player->pos_x = empty_place[0] + 0.5;
	wolf->player->pos_y = empty_place[1] + 0.5;
	free(empty_place);
}
