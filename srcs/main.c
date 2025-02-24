/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/27 19:58:38 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/27 19:58:41 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

int				main(int ac, char **av)
{
	t_wolf		wolf;

	if (ac != 2)
		error_exit(USAGE);
	check_map_format(av[1]);
	wolf_init(&wolf, av[1]);
	sdl_texture_init(&wolf);
	if (!check_norme(&wolf))
		error_exit(MAP_ERR);
	wolf.map->map = read_map(&wolf);
	edges_check(&wolf);
	load_all_textures(&wolf);
	do_work(&wolf);
	return (0);
}

int				check_map_format(char *file_name)
{
	char	**split;
	int		idx;
	int		fd;
	char	*tmp;

	tmp = NULL;
	idx = 0;
	split = NULL;
	fd = open(file_name, O_RDONLY);
	if (read(fd, tmp, 0) == -1)
		error_exit(FORMAT_ERR);
	close(fd);
	ft_strdel(&tmp);
	split = ft_strsplit(file_name, '.');
	while (split[idx])
		idx++;
	if (!ft_strequ(split[--idx], MAP_FORMAT))
	{
		clean_text(split);
		error_exit(FORMAT_ERR);
	}
	else
		clean_text(split);
	return (1);
}

static	void	wall_calculation(t_wolf *wolf, int x)
{
	do_dda(wolf);
	calc_cam_distance(wolf);
	calc_line_height(wolf);
	get_wall_color(wolf);
	SDL_RenderDrawLine(wolf->graph->render, x,
	wolf->player->start_draw, x, wolf->player->end_draw);
}

static	void	wall_text_calculation(t_wolf *wolf, int x)
{
	do_dda(wolf);
	calc_cam_distance(wolf);
	calc_line_height(wolf);
	calc_ray_texture_hit(wolf);
	set_line_pixels(wolf, wolf->text_numb, x);
}

void			do_work(t_wolf *wolf)
{
	int		is_running;
	int		x;

	is_running = 1;
	player_init(wolf);
	while (is_running)
	{
		x = -1;
		while (++x < wolf->scr_w)
		{
			sycle_init(wolf, x);
			do_step(wolf);
			if (wolf->graph->wall_text_preset == FLAT_TEXT)
				wall_calculation(wolf, x);
			else
				wall_text_calculation(wolf, x);
		}
		set_move_speed(wolf);
		if (interactive_elem(wolf) == -1)
		{
			is_running = 0;
			break ;
		}
	}
}
