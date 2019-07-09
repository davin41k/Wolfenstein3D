/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norminette_two.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/08 18:45:36 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/08 18:45:39 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		count_x(char *line)
{
	char		**splited;
	static	int	count;

	if (line == NULL)
		return (count);
	splited = ft_strsplit(line, ' ');
	while (splited[count])
		count++;
	clean_text(splited);
	return (count);
}

int		get_count_x(int x)
{
	static	int	count_x;

	if (x == GET_NUM)
		return (count_x);
	count_x = x;
	return (count_x);
}

int		get_count_y(int y)
{
	static	int	count_y;

	if (y == GET_NUM)
		return (count_y);
	return (++count_y);
}
