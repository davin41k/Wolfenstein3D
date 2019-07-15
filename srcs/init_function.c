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
	wolf->scr_w = WIN_HD_WIDTH;
	wolf->scr_h = WIN_HD_HEIGHT;
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
	plant_player(wolf);
	wolf->text_pack = TEXT_PACK_ONE;
	//printf("P_POS:\t%f\t%f\n", wolf->player->pos_x,  wolf->player->pos_y);
	//wolf->player->pos_x = 22; //22
	//wolf->player->pos_y = 12; // 12
	wolf->player->dir_x = -1;
	wolf->player->dir_y = 0;
	wolf->player->plane_x = 0;
	wolf->player->plane_y = 0.9; // 0.66
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
	graph->win = SDL_CreateWindow("Wolf3D", 250,
	250, wolf->scr_w, wolf->scr_h, SDL_WINDOW_SHOWN);
	if (graph->win == NULL)
		error_exit(MEM_ERR);
	//graph->win_surface = SDL_GetWindowSurface(graph->win);
	graph->render = SDL_CreateRenderer(graph->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (graph->render == NULL)
		error_exit(MEM_ERR);
	graph->screen = SDL_CreateRGBSurface(0, wolf->scr_w, wolf->scr_h, 32,
	0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if (graph->screen == NULL)
		error_exit(MEM_ERR);
	// graph->scr_pixels = (int)graph->screen->pixels;
	graph->wall_text_preset = FLAT_TEXT;
	graph->texture = SDL_CreateTexture(wolf->graph->render,
	SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, wolf->scr_w, wolf->scr_h);
	graph->pixs = ft_memalloc(sizeof(int) * (wolf->scr_h * wolf->scr_w));
	// printf("%p | %p\n", graph->screen, graph->win);
}
void	sdl_texture_init(t_wolf *wolf)
{
	t_graph		*graph;

	if ((SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0))
		error_exit(MEM_ERR);
	graph = wolf->graph;
	graph->win = SDL_CreateWindow("Wolf3D", 250,
	250, wolf->scr_w, wolf->scr_h, SDL_WINDOW_SHOWN);
	if (graph->win == NULL)
		error_exit(MEM_ERR);
	//graph->win_surface = SDL_GetWindowSurface(graph->win);
	graph->render = SDL_CreateRenderer(graph->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (graph->render == NULL)
		error_exit(MEM_ERR);
	graph->screen = SDL_CreateRGBSurface(0, wolf->scr_w, wolf->scr_h, 32,
	0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if (graph->screen == NULL)
		error_exit(MEM_ERR);
	// graph->scr_pixels = (int)graph->screen->pixels;
	graph->wall_text_preset = SPRITE_TEXT;
	graph->texture = SDL_CreateTexture(wolf->graph->render,
	SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, wolf->scr_w, wolf->scr_h);
	graph->pixs = ft_memalloc(sizeof(int) * (wolf->scr_h * wolf->scr_w));
	// printf("%p | %p\n", graph->screen, graph->win);
}

