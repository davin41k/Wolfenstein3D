/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 20:25:24 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/26 20:25:28 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		**read_map(t_wolf *wolf)
{
	int		**map;
	int		fd;
	char	*line;
	int		idx;

	idx = -1;
	fd = open(wolf->file_name, O_RDONLY);
	map = init_map_array();
	while (get_next_line(fd, &line))
	{
		map[++idx] = get_array_line(line);
	}
	return (map);
}

int		*get_array_line(char *line)
{
	int		*array;
	char	**splitted;
	int		idx;

	if (!(array = (int*)ft_memalloc(sizeof(int) * get_count_x(GET_NUM))))
		error_exit(MEM_ERR);
	splitted = ft_strsplit(line, ' ');
	idx = -1;
	while (splitted[++idx])
	{
		array[idx] = ft_getnbr(splitted[idx]);
	}
	clean_text(splitted);
	return (array);
}

int		**init_map_array(void)
{
	int		**map;
	int		idx;
	int		line_len;
	int		array_len;

	idx = -1;
	line_len = get_count_x(GET_NUM);
	array_len = get_count_y(GET_NUM);
	if (!(map = (int**)ft_memalloc(sizeof(int*) * (array_len + 1))))
		error_exit(MEM_ERR);
	map[array_len] = NULL;
	return (map);
}

void	print_map(t_wolf *wolf)
{
	int		**array;
	int		idx;
	int		len;
	int		i;

	array = wolf->map->map;
	len = get_count_x(GET_NUM);
	i = 0;
	while (array[i])
	{
		idx = -1;
		while (++idx < len)
		{
			ft_putnbr(array[i][idx]);
			ft_putstr("  ");
		}
		ft_putendl("");
		i++;
	}
}

void	edges_check(t_wolf *wolf)
{
	int		**map;
	int		i;
	int		endx;
	int		endy;

	map = wolf->map->map;
	i = -1;
	endx = get_count_x(GET_NUM);
	endy = get_count_y(GET_NUM);
	while (++i < endx)
		if (map[0][i] == 0)
			map[0][i] = 1;
	i = -1;
	while (++i < endx)
		if (map[endy - 1][i] == 0)
			map[endy - 1][i] = 1;
	i = -1;
	while (++i < endy)
		if (map[i][0] == 0)
			map[i][0] = 1;
	i = -1;
	while (++i < endy)
		if (map[i][endy - 1] == 0)
			map[i][endy - 1] = 1;
}
