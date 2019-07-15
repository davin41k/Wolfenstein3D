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
# define WIN_HD_HEIGHT	720
# define WIN_HD_WIDTH	1280

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
# define INCORRECT_MAP	4
# define LOAD_ERR		5

# define PALETTE_ONE	0
# define PALETTE_TWO	1
# define ON				1
# define OFF			0
# define MAX_ITTER		65

# define TEXTURES_COUNT	8
# define TEXTURES_W		64
# define TEXTURES_H		64
# define FLAT_TEXT		0
# define SPRITE_TEXT	1
# define TEXT_PACK_ONE	0
# define TEXT_PACK_TWO	4

# define WALK			5
# define RUN			10
# define EASY_ROTATE	1
# define FAST_ROTATE	3



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
# include "SDL.h"

typedef	struct		s_graphics
{
	SDL_Window		*win;
	SDL_Renderer	*render;
	SDL_Event		event;
	SDL_Surface		*screen;
	SDL_Surface		*win_surface;
	SDL_Texture		*texture;
	int				*scr_pixels;
	int				*pixs;
	int				wall_text_preset;
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
	int				textr_x;
	int				textr_y;
	double			hit_wallx; //int
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
	int				*textures[TEXTURES_COUNT];
	int				text_numb;
	int				text_pack;
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

int		norme_norminatte(int first_line, char *line, int fd);
int		check_norme(t_wolf *wolf);
int		check_line_correct(char *line);
int		is_number(char *str);

	//	***NORMINETTE_TWO***
int		count_x(char *line);
int		get_count_x(int x);
int		get_count_y(int y);

	//	***MAP_READER***
int     **init_map_array(void);
int		*get_array_line(char *line);
void	print_map(t_wolf *wolf);
int		**read_map(t_wolf *wolf);
void	edges_check(t_wolf *wolf);

	//	***INIT_FUNCTION***
int		wolf_init(t_wolf *wolf, char *file_name);
void	player_init(t_wolf *wolf, int x);
void	sdl_init(t_wolf *wolf);
void	sycle_init(t_wolf *wolf, int x);
void	textures_array_init(t_wolf *wolf);
void	sdl_texture_init(t_wolf *wolf);

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
void	move_forward(t_wolf *wolf);
void	move_back(t_wolf *wolf);
void	mouse_rotation(t_wolf *wolf, int x);
void	texture_wall_drawing(t_wolf *wolf);
void	change_text_pack(t_wolf *wolf);

	//	***DRAWING_TWO***
void	calc_ray_texture_hit(t_wolf *wolf);
void	set_line_pixels(t_wolf *wolf, int texture_numb, int x);
void	clean_buff_screen(t_wolf *wolf);
void	update_screen(t_wolf *wolf);

	//	***DRAW_TEXTURES***
void	load_all_textures (t_wolf *wolf);

// ***MAIN***
void	do_work(t_wolf *wolf);

//	***PLAYER***
void	plant_player(t_wolf *wolf);


void	show_picture(t_wolf *wolf);

#endif
