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
	int		ret;
	
	map = init_map_array();
	while ((ret = get_next_line(fd, &line)))
	{

	}

	return (map);
}

int		*get_array_line(char	*line)
{
	int		*array;
	char	**splitted;
	int		idx;

	if(!(array = (int*)ft_memalloc(sizeof(int) * get_count_x(GET_NUM))))
		error_exit(MEM_ERR);
	splitted = ft_strsplit(line, ' ');
	idx = -1;
	while (splitted[++idx])
	{
		array[idx] = ft_getnbr(splitted[idx]);
		splitted++;
	}
	return (array);
}

int     **init_map_array(void)
{
	int		**map;
	int		idx;
	int		line_len;
	int		array_len;

	idx = -1;
	line_len = get_count_x(GET_NUM);
	array_len = get_count_y(GET_NUM);
	if(!(map = (int**)ft_memalloc(sizeof(int*) * (array_len + 1))))
		error_exit(MEM_ERR);

	while (++idx < array_len)
	{
		if(!(map[idx] = (int*)ft_memalloc(sizeof(int) * line_len)))
			error_exit(MEM_ERR);
	}
	return (map);
}
