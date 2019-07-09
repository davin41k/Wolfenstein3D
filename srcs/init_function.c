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
	wolf->scr_w = 640;
	wolf->scr_h = 480;
	wolf->file_name = file_name;
	if(!(wolf->graph = (t_graph*)malloc(sizeof(t_graph))))
		error_exit(MEM_ERR);
	if(!(wolf->player = (t_player*)malloc(sizeof(t_player))))
		error_exit(MEM_ERR);
	if(!(wolf->map = (t_map*)malloc(sizeof(t_map))))
		error_exit(MEM_ERR);
	if(!(wolf->color = (t_color*)malloc(sizeof(t_color))))
		error_exit(MEM_ERR);
	return (1);
}
//	1
void	player_init(t_wolf *wolf, int x)
{
	wolf->player->pos_x = 22; //22
	wolf->player->pos_y = 12; // 12
	wolf->player->dir_x = -1;
	wolf->player->dir_y = 0;
	wolf->player->plane_x = 0;
	wolf->player->plane_y = 0.66;
	wolf->player->rot_speed = 3;
	wolf->player->move_acceler =  (double)WALK;//5.0;
	wolf->player->rot_acceler = 3.0;
	// timing initialization
	
}

void	sycle_init(t_wolf *wolf, int x)
{
	wolf->player->cam_x = 2 * x / (double)wolf->scr_w - 1;
	wolf->player->raydir_x = wolf->player->dir_x + wolf->player->plane_x * wolf->player->cam_x;
	wolf->player->raydir_y = wolf->player->dir_y + wolf->player->plane_y * wolf->player->cam_x;
	wolf->map->map_x = (int)(wolf->player->pos_x);
	wolf->map->map_y = (int)(wolf->player->pos_y);
	wolf->player->dist_dx = fabs(1 / wolf->player->raydir_x);	// mb 1.0 or 1.0f /
	wolf->player->dist_dy = fabs(1 / wolf->player->raydir_y);
	wolf->player->hit = 0;
	// wolf->player->hit_side = 0;
	// wolf->player->move_sp = 5;

	// wolf->player->rot_speed = 3;
	// wolf->player->move_acceler = 5.0;
	// wolf->player->rot_acceler = 3.0;
}

void	textures_array_init(t_wolf *wolf)	// не нужно
{
	int		idx;
	int		count_pixels;

	// if (!(wolf->textures = (int**)ft_memalloc(sizeof(int*) * (TEXTURES_COUNT + 1))))
	// 	error_exit(MEM_ERR);
	idx = -1;
	count_pixels = TEXTURES_W * TEXTURES_H;
	while (++idx < TEXTURES_COUNT)
	{
		if (!(wolf->textures[idx] = (int*)ft_memalloc(sizeof(int) * count_pixels)))
			error_exit(MEM_ERR);
	}
	wolf->textures[idx] = NULL;
}

void	sdl_init(t_wolf *wolf)
{
	t_graph		*graph;

	if ((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0))
		error_exit(MEM_ERR);
	graph = wolf->graph;
	graph->win = SDL_CreateWindow("Wolf3D", 100,
	100, wolf->scr_w, wolf->scr_h, SDL_WINDOW_SHOWN);
	if (graph->win == NULL)
		error_exit(MEM_ERR);
	graph->render = SDL_CreateRenderer(graph->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (graph->render == NULL)
		error_exit(MEM_ERR);
	// graph->screen = SDL_GetWindowSurface(graph->win); SEGFOLT
	// graph->scr_pixels = (int*)graph->screen->pixels;
}
