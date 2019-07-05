/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <dshereme@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/15 17:14:46 by dshereme          #+#    #+#             */
/*   Updated: 2019/05/22 20:00:27 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef FRACTOL_H

# define FRACTOL_H

# define WIN_FHD_HEIGHT 1080
# define WIN_FHD_WIDTH	1080
# define WIN_HD_HEIGHT	560
# define WIN_HD_WIDTH	560
# define W				512
# define H				384

# define GET_NUM		0
# define INCREASE		1

# define _USE_MATH_DEFINES
# define TRU			1
# define FALSE			0
# define MALDEBROT		1
# define JULIA			2
# define BURN_SHIP		3

# define USAGE			0
# define THREAD_ERR		1
# define MEM_ERR		2
# define MAP_ERR		3

# define PALETTE_ONE	0
# define PALETTE_TWO	1
# define ON				1
# define OFF			0
# define MAX_ITTER		65

# define PLUS_KEY		24
# define MINUS_KEY		27
# define MULTIPLE_KEY	67
# define DIVISION_KEY	75
# define ESCAPE			53
# define TAB			48
# define SPACE			49
# define SCROLL_UP		4
# define SCROLL_DOWN	5
# define I_KEY			34

# define UP_KEY			126
# define DOWN_KEY		125
# define LEFT_KEY		123
# define RIGHT_KEY		124

# include <mlx.h>
# include <math.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "../libft/libft.h"
# include "../get_next_line/get_next_line.h"
# include <unistd.h>
# include <pthread.h>
# include <SDL2/SDL.h>

typedef	struct		s_graphics
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		event;
}					t_graph;

typedef	struct		s_player
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			cam_x;
	double			raydir_x;
	double			raydir_y;
	double			side_dst_x;
	double			side_dst_y;
	double			dist_dx;
	double			dist_dy;
	double			pwall_dst;
	double			move_sp;
	double			rot_speed;
	double			move_acceler;
	double			rot_acceler;
	int				step_x;
	int				step_y;
	int				hit;
	int				hit_side;
	int				line_height;
	int				start_draw;
	int				end_draw;
}					t_player;

typedef	struct		s_map
{
	int				**map;
	int				map_w;
	int				map_h;
	int				map_x;
	int				map_y;
}					t_map;

typedef	struct		s_color
{
	int				red;
	int				green;
	int				blue;
	int				color;		// :)
}					t_color;

typedef	struct		s_wolf
{
	int				scr_h;
	int				scr_w;
	char			*file_name;
	t_graph			*graph;
	t_player		*player;
	t_map			*map;
	t_color			*color;
}					t_wolf;

	//	***EXITS***
int		escape_exit(int key, t_wolf *wolf);
int		red_exit(int key, t_wolf *wolf);
void	read_error(void);
void	error_exit(int errno);

	//	***CLEAN FUNCTIONS***
void	clean_text(char **splitted);

	//	***NORMINATTE***
int		count_x(char *line);
int		get_count_x(int x);
int		get_count_y(int y);
int		norme_norminatte(int first_line, char *line, int fd);
int		check_norme(t_wolf *wolf);
int		check_line_correct(char *line);
int		is_number(char *str);

	//	***MAP_READER***
int     **init_map_array(void);
int		*get_array_line(char *line);
void	print_map(t_wolf *wolf);
int		**read_map(t_wolf *wolf);

	//	***INIT_FUNCTION***
int		wolf_init(t_wolf *wolf, char *file_name);
void	player_init(t_wolf *wolf, int x);
void	sdl_init(t_wolf *wolf);
void	sycle_init(t_wolf *wolf, int x);

	//	***DRAWING***
void	do_step(t_wolf *wolf);
void	do_dda(t_wolf *wolf);
void	calc_cam_distance(t_wolf *wolf);
void	calc_line_height(t_wolf *wolf);
void	get_wall_color(t_wolf *wolf);
void	wall_drawing(t_wolf *wolf);
double	get_fps(t_wolf *wolf);
int		interactive_elem(t_wolf *wolf);
void	do_move(t_wolf *wolf);
void	rotate_right(t_wolf *wolf);
void	rotate_left(t_wolf *wolf);
void	set_move_speed(t_wolf *wolf, double fps);

// ***MAIN***
void	do_work(t_wolf *wolf);

#endif
