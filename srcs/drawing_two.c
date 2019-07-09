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
void	calc_ray_texture_hit(t_wolf *wolf)
{
	t_player	*p;
//	int			text_numb;

	wolf->text_numb = wolf->map->map[wolf->map->map_x][wolf->map->map_y];
	p = wolf->player;

	if (!p->hit_side)
		p->hit_wallx = p->pos_y + p->pwall_dst * p->raydir_y;
	else
		p->hit_wallx = p->pos_x + p->pwall_dst * p->raydir_x;
	p->hit_wallx -= floor(p->hit_wallx);
	p->textr_x = (int)(p->hit_wallx * (double)TEXTURES_W);
	if (!p->hit_side && p->raydir_x > 0)
		p->textr_x = TEXTURES_W - p->textr_x - 1;
	else if (p->hit_side == 1 && p->raydir_x < 0)
		p->textr_x = TEXTURES_W - p->textr_x - 1;

}

void	set_line_pixels(t_wolf *wolf, int texture_numb, int x)
{
	int			color;
	int			tmp;
	int			y;
	t_player	*p;

	p = wolf->player;
	y = wolf->player->start_draw - 1;
	while (++y < wolf->player->end_draw)
	{
		tmp = y * 256 - wolf->scr_h * 128 + wolf->player->line_height * 128;
		p->textr_y = ((tmp * TEXTURES_H) / wolf->player->line_height) / 256;
		color = wolf->textures[texture_numb][TEXTURES_H * p->textr_y];
		if (p->hit_side == 1)
			color /= 1.4;
		wolf->graph->scr_pixels[y * wolf->scr_w - (wolf->scr_w - x)] = color; // записть ;нужного; текселя
	}

}

void	clean_buff_screen(t_wolf *wolf)
{
	int		idx;
	int		y_count;
	idx = -1;
	while (++y_count < wolf->scr_w)
	{
		idx = -1;
		while (++idx < wolf->scr_h)
		{
			wolf->graph->scr_pixels[idx + y_count * wolf->scr_w] = 0;
		}
	}
}
