/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drwing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/25 19:57:19 by dshereme          #+#    #+#             */
/*   Updated: 2019/06/25 19:57:20 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void		move_forward(t_wolf *wolf)
{
	if (wolf->map->map[(int)(wolf->player->pos_x + wolf->player->dir_x *
		wolf->player->move_sp + WALL_STOPPER)]
		[(int)(wolf->player->pos_y)] == 0 &&
		!(wolf->map->map[(int)(wolf->player->pos_x + wolf->player->dir_x *
		wolf->player->move_sp - WALL_STOPPER)]
		[(int)(wolf->player->pos_y)]))
		wolf->player->pos_x += wolf->player->dir_x * wolf->player->move_sp;
	if (wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y + wolf->player->dir_y *
	wolf->player->move_sp + WALL_STOPPER)] == 0 &&
	!(wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y + wolf->player->dir_y *
	wolf->player->move_sp - WALL_STOPPER)]))
		wolf->player->pos_y += wolf->player->dir_y * wolf->player->move_sp;
}

void		move_back(t_wolf *wolf)
{
	if (wolf->map->map[(int)(wolf->player->pos_x - wolf->player->dir_x *
		wolf->player->move_sp + WALL_STOPPER)]
		[(int)(wolf->player->pos_y)] == 0 &&
		(wolf->map->map[(int)(wolf->player->pos_x - wolf->player->dir_x *
		wolf->player->move_sp - WALL_STOPPER)]
		[(int)(wolf->player->pos_y)]) == 0)
		wolf->player->pos_x -= wolf->player->dir_x * wolf->player->move_sp;
	if (wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y - wolf->player->dir_y *
	wolf->player->move_sp + WALL_STOPPER)] == 0 &&
	(wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y - wolf->player->dir_y *
	wolf->player->move_sp - WALL_STOPPER)]) == 0)
		wolf->player->pos_y -= wolf->player->dir_y *
		wolf->player->move_sp;
}

void		rotate_right(t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player->dir_x;
	old_plane_x = wolf->player->plane_x;
	wolf->player->dir_x = wolf->player->dir_x * cos(-wolf->player->rot_speed)
	- wolf->player->dir_y * sin(-wolf->player->rot_speed);
	wolf->player->dir_y = old_dir_x * sin(-wolf->player->rot_speed) +
	wolf->player->dir_y * cos(-wolf->player->rot_speed);
	wolf->player->plane_x = wolf->player->plane_x *
	cos(-wolf->player->rot_speed) - wolf->player->plane_y
	* sin(-wolf->player->rot_speed);
	wolf->player->plane_y = old_plane_x * sin(-wolf->player->rot_speed)
	+ wolf->player->plane_y * cos(-wolf->player->rot_speed);
}

void		rotate_left(t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player->dir_x;
	old_plane_x = wolf->player->plane_x;
	wolf->player->dir_x = wolf->player->dir_x * cos(wolf->player->rot_speed)
	- wolf->player->dir_y * sin(wolf->player->rot_speed);
	wolf->player->dir_y = old_dir_x * sin(wolf->player->rot_speed) +
	wolf->player->dir_y * cos(wolf->player->rot_speed);
	wolf->player->plane_x = wolf->player->plane_x *
	cos(wolf->player->rot_speed) - wolf->player->plane_y *
	sin(wolf->player->rot_speed);
	wolf->player->plane_y = old_plane_x * sin(wolf->player->rot_speed) +
	wolf->player->plane_y * cos(wolf->player->rot_speed);
}

void		mouse_rotation(t_wolf *wolf, int x)
{
	static	int		old_x;

	if (!old_x)
		old_x = x;
	if (old_x < x)
	{
		rotate_right(wolf);
		old_x = x;
	}
	else if (old_x > x)
	{
		rotate_left(wolf);
		old_x = x;
	}
}
