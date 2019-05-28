/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 18:29:17 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/27 18:29:19 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	clean_text(char **splitted)
{
	int		i;

	i = -1;
	while (splitted[++i])
		free(splitted[i]);
	free(splitted);
}
