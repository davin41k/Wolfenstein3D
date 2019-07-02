/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 17:03:14 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/01 17:03:16 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"


//	1
void	calc_ray_pos(t_wolf *wolf, int x)
{
	t_player	*p;

	p = wolf->player;
	p->cam_x = 2 * x / (double) wolf->scr_w - 1;
	p->raydir_x = p->dir_x + p->plane_x * p->cam_x;
	p->raydir_y = = p->dir_y + p->plane_y * p->cam_x;
	wolf->map->map_x = (int)p->pos_x;
	wolf->map->map_y = (int)p->pos_y;
	p->dist_dx = fabs(1 / p->raydir_x);
	p->dist_dy = fabs(1 / p->raydir_y);
}
