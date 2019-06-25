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
	fd = open (wolf->file_name, O_RDONLY);
	printf("FDGDGDG\n");
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
	printf("ARR_LINE\n");

	if(!(array = (int*)ft_memalloc(sizeof(int) * get_count_x(GET_NUM))))
		error_exit(MEM_ERR);
	splitted = ft_strsplit(line, ' ');
	idx = -1;
	printf("C_X:\t%d\n", get_count_x(GET_NUM));
	while (splitted[++idx])
	{
		printf("SPLITED:\t%s\n", splitted[idx]);
		array[idx] = ft_getnbr(splitted[idx]);
		//splitted++;
	}
	clean_text(splitted);
	printf("ARR_LINE\n");
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
	map[array_len] = NULL;

	// while (++idx < array_len)
	// {
	// 	if(!(map[idx] = (int*)ft_memalloc(sizeof(int) * line_len)))
	// 		error_exit(MEM_ERR);
	// }
	printf("FDGDGDG\n");
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
	while(array[i])
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
