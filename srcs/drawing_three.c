/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_three.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:14:17 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/15 19:14:24 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		do_step(t_wolf *wolf)
{
	if (wolf->player->raydir_x < 0)
	{
		wolf->player->step_x = -1;
		wolf->player->side_dst_x = (wolf->player->pos_x - wolf->map->map_x)
		* wolf->player->dist_dx;
	}
	else
	{
		wolf->player->step_x = 1;
		wolf->player->side_dst_x = (wolf->map->map_x + 1.0 -
		wolf->player->pos_x) * wolf->player->dist_dx;
	}
	if (wolf->player->raydir_y < 0)
	{
		wolf->player->step_y = -1;
		wolf->player->side_dst_y = (wolf->player->pos_y - wolf->map->map_y)
		* wolf->player->dist_dy;
	}
	else
	{
		wolf->player->step_y = 1;
		wolf->player->side_dst_y = (wolf->map->map_y + 1.0 -
		wolf->player->pos_y) * wolf->player->dist_dy;
	}
}

void		do_dda(t_wolf *wolf)
{
	while (wolf->player->hit == 0)
	{
		if (wolf->player->side_dst_x < wolf->player->side_dst_y)
		{
			wolf->player->side_dst_x += wolf->player->dist_dx;
			wolf->map->map_x += wolf->player->step_x;
			wolf->player->hit_side = 0;
		}
		else
		{
			wolf->player->side_dst_y += wolf->player->dist_dy;
			wolf->map->map_y += wolf->player->step_y;
			wolf->player->hit_side = 1;
		}
		if (wolf->map->map[wolf->map->map_x][wolf->map->map_y] > 0)
			wolf->player->hit = 1;
	}
}

void		calc_cam_distance(t_wolf *wolf)
{
	if (wolf->player->hit_side == 0)
		wolf->player->pwall_dst = (wolf->map->map_x - wolf->player->pos_x
		+ (1 - wolf->player->step_x) / 2) / wolf->player->raydir_x;
	else
		wolf->player->pwall_dst = (wolf->map->map_y - wolf->player->pos_y
		+ (1 - wolf->player->step_y) / 2) / wolf->player->raydir_y;
}

void		calc_line_height(t_wolf *wolf)
{
	int		line_height;
	int		start;
	int		end;

	line_height = (int)(wolf->scr_h / wolf->player->pwall_dst);
	start = -line_height / 2 + wolf->scr_h / 2;
	end = line_height / 2 + wolf->scr_h / 2;
	if (start < 0)
		start = 0;
	if (end >= wolf->scr_h)
		end = wolf->scr_h - 1;
	wolf->player->line_height = line_height;
	wolf->player->start_draw = start;
	wolf->player->end_draw = end;
}

void		wall_drawing(t_wolf *wolf)
{
	SDL_RenderPresent(wolf->graph->render);
	SDL_SetRenderDrawColor(wolf->graph->render, 0, 0, 0, 255);
	SDL_RenderClear(wolf->graph->render);
}
