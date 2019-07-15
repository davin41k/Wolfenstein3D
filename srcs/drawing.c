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

void		get_wall_color(t_wolf *wolf)
{
	int		color;

	color = wolf->map->map[wolf->map->map_x][wolf->map->map_y];
	if (color == 1)
		wolf->color->color = 0xFF0000;//16711680;//0xFF0000;
	else if (color == 2)
		wolf->color->color = 0x008000;//65280;//0x008000;
	else if (color == 3)
		wolf->color->color = 0x0000FF;//255;//0x0000FF;
	else if (color == 4)
		wolf->color->color = 0;//0xFFFFFF;
	 else if (color == 5)
	 	wolf->color->color = 0xFFFF00;
	else
		wolf->color->color = 16776960;
	if (wolf->player->hit_side == 1)
		wolf->color->color /= 1.5;
	SDL_SetRenderDrawColor(wolf->graph->render, wolf->color->color >> 16,
	wolf->color->color >> 8, wolf->color->color, 255);
}

void		wall_drawing(t_wolf *wolf)
{
	SDL_RenderPresent(wolf->graph->render);
	SDL_SetRenderDrawColor(wolf->graph->render, 0,  0, 0, 255);
	SDL_RenderClear(wolf->graph->render);
}
void		texture_wall_drawing(t_wolf *wolf)
{
	//SDL_BlitSurface(wolf->graph->screen, NULL, wolf->graph->win, NULL);
	//SDL_UpdateWindowSurface(wolf->graph->win);
	update_screen(wolf);
	int		i, j;
	i = -1;
	int pix = -1;
	while (++i < wolf->scr_h)
	{
		j = -1;
		while (++j < wolf->scr_w)
		wolf->graph->pixs[++pix] = 0;
	}
}
//8
double		get_fps(t_wolf *wolf)
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
	double	frame_time;
	frame_time = get_fps(wolf);
	if (wolf->graph->wall_text_preset == FLAT_TEXT)
		wall_drawing(wolf);
	else
		texture_wall_drawing(wolf);
	wolf->player->move_sp = frame_time * wolf->player->move_acceler;
	wolf->player->rot_speed = frame_time * wolf->player->rot_acceler;
}

int			interactive_elem(t_wolf *wolf)
{
	t_graph		*g;

	g = wolf->graph;
	SDL_PollEvent(&g->event);
	if((SDL_QUIT == g->event.type) || (SDL_KEYDOWN == g->event.type &&
	SDL_SCANCODE_ESCAPE == g->event.key.keysym.scancode))
			return (-1);
	else if (g->event.type == SDL_KEYDOWN)
	{
		if (g->event.key.keysym.sym == SDLK_w || g->event.key.keysym.sym ==
		SDLK_s ||g->event.key.keysym.sym == SDLK_a ||
		g->event.key.keysym.sym == SDLK_d)
			do_move(wolf);
		else if (g->event.key.keysym.sym == SDLK_LSHIFT)
			wolf->player->move_acceler = (double)RUN;
		else if (g->event.key.keysym.sym == SDLK_t)
			change_text_pack(wolf);
	}
	else if (g->event.type == SDL_MOUSEMOTION)
		mouse_rotation(wolf, g->event.button.x);
	else if (g->event.type == SDL_KEYUP)
		if (g->event.key.keysym.sym == SDLK_LSHIFT)
			wolf->player->move_acceler = (double)WALK;
	return (0);
}

void		do_move(t_wolf *wolf)
{
	if (wolf->graph->event.key.keysym.sym == SDLK_w)
		move_forward(wolf);
	if (wolf->graph->event.key.keysym.sym == SDLK_s)
		move_back(wolf);
	if (wolf->graph->event.key.keysym.sym == SDLK_d)
		rotate_right(wolf);
	if (wolf->graph->event.key.keysym.sym == SDLK_a)
		rotate_left(wolf);
}

void		move_forward(t_wolf *wolf)
{
	if (wolf->map->map[(int)(wolf->player->pos_x + wolf->player->dir_x *
		wolf->player->move_sp)][(int)(wolf->player->pos_y)] == 0)
			wolf->player->pos_x += wolf->player->dir_x * wolf->player->move_sp;
	if (wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y + wolf->player->dir_y *
	wolf->player->move_sp)] == 0)
		wolf->player->pos_y += wolf->player->dir_y * wolf->player->move_sp;
}

void		move_back(t_wolf *wolf)
{
	if (wolf->map->map[(int)(wolf->player->pos_x - wolf->player->dir_x *
		wolf->player->move_sp)][(int)(wolf->player->pos_y)] == 0)
			wolf->player->pos_x -= wolf->player->dir_x * wolf->player->move_sp;
	if (wolf->map->map[(int)(wolf->player->pos_x)]
	[(int)(wolf->player->pos_y - wolf->player->dir_y *
	wolf->player->move_sp)] == 0)
		wolf->player->pos_y -= wolf->player->dir_y *
		wolf->player->move_sp;
}

void		rotate_right(t_wolf *wolf)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = wolf->player->dir_x;
	old_plane_x =wolf->player->plane_x;
	wolf->player->dir_x =  wolf->player->dir_x * cos(-wolf->player->rot_speed)
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
	old_plane_x =wolf->player->plane_x;
	wolf->player->dir_x =  wolf->player->dir_x * cos(wolf->player->rot_speed)
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

void		change_text_pack(t_wolf *wolf)
{
	if (wolf->text_pack == TEXT_PACK_ONE)
		wolf->text_pack = TEXT_PACK_TWO;
	else
		wolf->text_pack = TEXT_PACK_ONE;
}
