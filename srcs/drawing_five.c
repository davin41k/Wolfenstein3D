/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_five.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 19:16:36 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/15 19:16:37 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

void	change_text_pack(t_wolf *wolf)
{
	if (wolf->text_pack == TEXT_PACK_ONE)
		wolf->text_pack = TEXT_PACK_TWO;
	else
		wolf->text_pack = TEXT_PACK_ONE;
}

void	sdl_init(t_wolf *wolf)
{
	t_graph		*graph;

	if ((SDL_Init(SDL_INIT_VIDEO) != 0))
		error_exit(MEM_ERR);
	graph = wolf->graph;
	graph->win = SDL_CreateWindow("Wolf3D", 250,
	250, wolf->scr_w, wolf->scr_h, SDL_WINDOW_SHOWN);
	if (graph->win == NULL)
		error_exit(MEM_ERR);
	graph->render = SDL_CreateRenderer(graph->win, -1,
	SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (graph->render == NULL)
		error_exit(MEM_ERR);
	graph->screen = SDL_CreateRGBSurface(0, wolf->scr_w, wolf->scr_h, 32,
	0xff000000, 0x00ff0000, 0x0000ff00, 0x000000ff);
	if (graph->screen == NULL)
		error_exit(MEM_ERR);
	graph->wall_text_preset = FLAT_TEXT;
	graph->texture = SDL_CreateTexture(wolf->graph->render,
	SDL_PIXELFORMAT_ARGB8888,
	SDL_TEXTUREACCESS_STREAMING, wolf->scr_w, wolf->scr_h);
	graph->pixs = ft_memalloc(sizeof(int) * (wolf->scr_h * wolf->scr_w));
}

void	show_picture(t_wolf *wolf)
{
	int		x;
	int		y;
	int		last_pix;
	int		*arr;
	int		i;

	i = -1;
	x = -1;
	y = -1;
	last_pix = TEXTURES_W * TEXTURES_H;
	arr = wolf->graph->scr_pixels;
	while (++y < 64)
	{
		x = -1;
		while (++x < 64)
		{
			i++;
			arr[x + y * wolf->scr_w] = wolf->textures[0][TEXTURES_W * y + x];
		}
	}
}

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
		wolf->color->color = 0;
	else if (color == 5)
		wolf->color->color = 0xFFFF00;
	else
		wolf->color->color = 16776960;
	if (wolf->player->hit_side == 1)
		wolf->color->color /= 1.5;
	SDL_SetRenderDrawColor(wolf->graph->render, wolf->color->color >> 16,
	wolf->color->color >> 8, wolf->color->color, 255);
}
