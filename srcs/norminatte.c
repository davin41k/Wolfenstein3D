/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminatte.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/26 20:37:06 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/26 20:37:08 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

static	void	check_map_correct(t_wolf *wolf)
{
	int		count_x;
	int		count_y;

	count_x = get_count_x(GET_NUM);
	count_y = get_count_y(GET_NUM);
	printf("%d, %d  \n",get_count_x(GET_NUM), get_count_y(GET_NUM));
	if (count_x < 4 || count_y < 4 || count_x > 120 ||  count_y > 120)
		error_exit(INCORRECT_MAP);
}

int				check_norme(t_wolf *wolf)
{
	int		fd;
	char	*line;
	int		ret;
	int		first_line;

	fd = open(wolf->file_name, O_RDONLY);
	first_line = -1;
	while ((ret = get_next_line(fd, &line)))
	{
		if (ret < 0)
			error_exit(2);
		get_count_y(INCREASE);
		if (first_line == -1)
			first_line = count_x(line);
		if (!norme_norminatte(first_line, line, fd))
			return (0);
		free(line);
	}
	free(line);
	get_count_x(first_line);
	check_map_correct(wolf);
	close(fd);
	return (1);
}

int				norme_norminatte(int first_line, char *line, int fd)
{
	if (!check_line_correct(line))
	{
		free(line);
		close(fd);
		return (0);
	}
	if (first_line != count_x(line) || first_line < 2)
	{
		free(line);
		close(fd);
		return (0);
	}
	return (1);
}

int				check_line_correct(char *line)
{
	char	**splitted;
	int		idx;

	splitted = ft_strsplit(line, ' ');
	idx = -1;
	while (splitted[++idx])
	{
		if (!is_number(splitted[idx]))
		{
			clean_text(splitted);
			return (0);
		}
	}
	clean_text(splitted);
	return (1);
}

int				is_number(char *str)
{
	//int		i = ft_getnbr(str);
	while (*str)
	{
		if (!ft_isdigit((*str)))
			return (0);
		if (ft_atoi(&(*str)) > 4)
			return (0);
		str++;
	}
	return (1);
}
