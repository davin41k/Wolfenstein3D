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

#include "../includes/wolf.h"

int		main(int ac, char **av)
{
	t_wolf		wolf;
	t_map		map;

	wolf_init(&wolf, av[1]);
	sdl_init(&wolf);
	//wolf.file_name = av[1];
	if (!check_norme(&wolf))
		error_exit(MAP_ERR);
	wolf.map->map = read_map(&wolf);
	print_map(&wolf);
	do_work(&wolf);

	return (0);
}

static	void	wall_calculation(t_wolf *wolf, int x)
{
	do_dda(wolf);
	calc_cam_distance(wolf);
	calc_line_height(wolf);
	get_wall_color(wolf);
	SDL_RenderDrawLine(wolf->graph->render, x, wolf->player->start_draw, x, wolf->player->end_draw);
	//printf("DRAW LINE\n");
	
}

void	do_work(t_wolf *wolf)
{
	int		is_running;
	int		x;

	
	is_running = 1;
	player_init(wolf, x);
	while (is_running)
	{
		x = -1;
		while (++x < wolf->scr_w)
		{
			sycle_init(wolf, x);
			do_step(wolf);
			wall_calculation(wolf, x);
		}
		set_move_speed(wolf, x);
		//wall_drawing(wolf); //
		if (interactive_elem(wolf) == -1)			//add norm
		{ is_running = 0;//
			break ;//
		}
	}
	// do_step(wolf);

}

//void	show_map()
