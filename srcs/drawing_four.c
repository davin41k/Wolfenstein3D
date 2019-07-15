/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_four.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:15:29 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/15 19:15:30 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void		texture_wall_drawing(t_wolf *wolf)
{
	int		i;
	int		j;
	int		pix;

	update_screen(wolf);
	i = -1;
	pix = -1;
	while (++i < wolf->scr_h)
	{
		j = -1;
		while (++j < wolf->scr_w)
			wolf->graph->pixs[++pix] = 0;
	}
}

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
	double		frame_time;

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
	if ((SDL_QUIT == g->event.type) || (SDL_KEYDOWN == g->event.type &&
	SDL_SCANCODE_ESCAPE == g->event.key.keysym.scancode))
		return (-1);
	else if (g->event.type == SDL_KEYDOWN)
	{
		if (g->event.key.keysym.sym == SDLK_w || g->event.key.keysym.sym ==
		SDLK_s || g->event.key.keysym.sym == SDLK_a ||
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
