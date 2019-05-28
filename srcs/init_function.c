/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_function.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 12:19:45 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/28 12:19:47 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		wolf_init(t_wolf *wolf, char *file_name)
{
	wolf->file_name = file_name;
	if(!(wolf->graph = (t_graph*)malloc(sizeof(t_graph))))
		error_exit(MEM_ERR);
	if(!(wolf->player = (t_player*)malloc(sizeof(t_player))))
		error_exit(MEM_ERR);
	if(!(wolf->map = (t_map*)malloc(sizeof(t_map))))
		error_exit(MEM_ERR);
	return (1);
}
