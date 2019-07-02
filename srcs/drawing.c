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

#include "../includes/wolf.h"
//	2
void	do_step(t_wolf *wolf)
{
	if (wolf->player->raydir_x < 0)
	{
		wolf->player->step_x = -1;
		wolf->player->side_dst_x = (wolf->player->pos_x - wolf->map->map_x) * wolf->player->dist_dx;
	}
	else
	{
		wolf->player->step_x = 1;
		wolf->player->side_dst_x = (wolf->map->map_x + 1.0 - wolf->player->wolf->player->pos_x) * wolf->player->dist_dx;
	}
	if (wolf->player->raydir_y < 0)
	{
		wolf->player->step_y = 1;
		wolf->player->side_dst_y = (wolf->player->pos_y - wolf->map->map_y) * wolf->player->dist_dy;
	}
	else
	{
		wolf->player->step_y = 1;
		wolf->player->side_dst_y = (wolf->map->map_y + 1.0 - wolf->player->pos_y) * wolf->player->dist_dy;
	}	
}
//	3
void	do_dda(t_wolf *wolf)
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
			hit = 1;
	}
}
//4
void	calc_cam_distance(t_wolf *wolf)
{
	if (!wolf->player->hit_side)
		wolf->player->pwall_dst = (wolf->player->map_x - wolf->player->pos_x
		+ (1 - wolf->player->step_x) / 2) / wolf->player->raydir_x;
	else
		wolf->player->pwall_dst = (wolf->player->map_y - wolf->player->pos_y
		+ (1 - wolf->player->step_y) / 2) / wolf->player->raydir_y;
}
//5
void	calc_line_height(t_wolf *wolf)
{
	int		line_height;
	int		start;
	int		end;

	line_height = (int)(wolf->scr_h / wolf->player->pwall_dst);
	start = -line_height / 2 + wolf->h / 2;
	end = line_height / 2 + wolf->h / 2;
	if (start < 0)
		start = 0;
	if (end >= wolf->h)
		end = wolf->h - 1;
	wolf->player->line_height = line_height;
	wolf->player->start_draw = start;
	wolf->player->end_draw = end;
}
//	6
void	get_wall_color(t_wolf *wolf)
{
	int		color;

	color = wolf->map->map[wolf->map->map_x][wolf->map->map_y];
	if (color == 1)
		wolf->color->color = 0xFF0000;
	else if (color == 2)
		wolf->color->color = 0x008000;
	else if (color == 3)
		wolf->color->color = 0x0000FF;
	else if (color == 4)
		wolf->color->color = 0xFFFFFF;
	else if (color == 5)
		wolf->color->color = 0xFFFF00;
	if (wolf->player->hit_side == 1)
		color = color / 2;
	SDL_SetRenderDrawColor(wolf->graph->render, color >> 16 , color >> 8, color, 255);
}
// 7
void	wall_drawing(t_wolf *wolf)
{
	//SDL_RenderDrawLine(wolf->graph->render, x, wolf->player->start_draw, x, wolf->player->end_draw);
	SDL_RenderPresent(wolf->graph->render);
	SDL_SetRenderDrawColor(wolf->graph->render, 0,  0, 0, 255);
	SDL_RenderClear(wolf->graph->render);

}
//8
static	double	get_fps(t_wolf *wolf)
{
	double			time;
	static	double	old_time;
	double			frame_time;

	time = SDL_GetTicks();
	frame_time = (time - old_time) / 1000.0;
	old_time = time;
	return (frame_time);
}

void		set_move_speed(t_wolf *wolf, double fps)
{
	double	f_time;

	f_time = get_fps(wolf);
	wolf->player->move_sp = f_time * wolf->player->move_acceler;
	wolf->player->rot_speed = f_time * wolf->player->rot_acceler;
}

//	9			re -1 == break
int			interactive_elem(t_wolf *wolf)
{
	t_graph		*g;

	g = wolf->graph->event;
	if (SDL_PollEvent(&h->event) && event.type == SDL_QUIT)
			return (-1);
	else if (g->event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_w || event.key.keysym.sym == SDLK_s ||
		event.key.keysym.sym == SDLK_a ||event.key.keysym.sym == SDLK_d ||)
			do_move(wolf)
	}
}

void	do_move(t_wolf *wolf)
{
	double	frame_time;

	frame_time = get_fps(wolf);
	wolf->player->move_sp = frame_time * 5.0;
	wolf->player->rot_speed = frame_time * 3.0;
	if (wolf->graph->event.key.keysym.sym == SDLK_w)
	{
		if (wolf->map->map[int(wolf->player->pos_x + wolf->player->dir_x * wolf->player->move_sp)][int(wolf->player->pos_y)] == 0)
			wolf->player->pos_x += wolf->player->dir_x * wolf->player->move_sp;
		if (wolf->map->map[int(wolf->player->pos_x)][int(wolf->player->pos_x + wolf->player->dir_x * wolf->player->move_sp)] == 0)
			wolf->player->pos_y += wolf->player->dir_y * wolf->player->move_sp;
	}
	if (keyDown(wolf->graph->event.key.keysym.sym == SDLK_s))
	{
		if (wolf->map->map[int(wolf->player->pos_x - wolf->player->dir_x * wolf->player->move_sp)][int(wolf->player->pos_y)] == 0)
			wolf->player->pos_x -= wolf->player->dir_x * wolf->player->move_sp;
		if (wolf->map->map[int(wolf->player->pos_x)][int(wolf->player->pos_x - wolf->player->dir_x * wolf->player->move_sp)] == 0)
			wolf->player->pos_y -= wolf->player->dir_y * wolf->player->move_sp;
	}
	if (keyDown(wolf->graph->event.key.keysym.sym == SDLK_a))
		rotate_right(wolf);
	if (keyDown(wolf->graph->event.key.keysym.sym == SDLK_d)
		rotate_left(wolf);
}

void	rotate_right(t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player->dir_x;
	old_plane_x =wolf->player->plane_x;
	wolf->player->dir_x =  wolf->player->dir_x * cos(-wolf->player->rot_speed) - wolf->player->dir_y * sin(-wolf->player->rot_speed);
	wolf->player->dir_y = old_dir_x * sin(-wolf->player->rot_speed) + wolf->player->dir_y * cos(-wolf->player->rot_speed);
	wolf->player->plane_x = wolf->player->plane_x * cos(-wolf->player->rot_speed) - wolf->player->plane_y * sin(-wolf->player->rot_speed);
	wolf->player->plane_y = old_plane_x * sin(-wolf->player->rot_speed) + wolf->player->plane_y * cos(-wolf->player->rot_speed);

}

void	rotate_left(t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player->dir_x;
	old_plane_x =wolf->player->plane_x;
	wolf->player->dir_x =  wolf->player->dir_x * cos(wolf->player->rot_speed) - wolf->player->dir_y * sin(wolf->player->rot_speed);
	wolf->player->dir_y = old_dir_x * sin(wolf->player->rot_speed) + wolf->player->dir_y * cos(wolf->player->rot_speed);
	wolf->player->plane_x = wolf->player->plane_x * cos(wolf->player->rot_speed) - wolf->player->plane_y * sin(wolf->player->rot_speed);
	wolf->player->plane_y = old_plane_x * sin(wolf->player->rot_speed) + wolf->player->plane_y * cos(wolf->player->rot_speed);
}
