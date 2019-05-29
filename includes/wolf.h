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

typedef	struct		s_graphics
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img;
	char			*data;
}					t_graph;

typedef	struct		s_player
{
	double			p_x;
	double			p_y;
	double			dir_x;
	double			dir_y;

}					t_player;

typedef	struct		s_map
{
	int				**map;
}					t_map;

typedef	struct		s_color
{
	int				red;
	int				green;
	int				blue;

}					t_color;

typedef	struct		s_wolf
{
	char			*file_name;
	t_graph			*graph;
	t_player		*player;
	t_map			*map;
}					t_wolf;

	//	***EXITS***
int		escape_exit(int key, t_wolf *wolf);
int		red_exit(int key, t_wolf *wolf);
void	read_error(void);
void	error_exit(int errno);

	//	***CLEAN FUNCTIONS***
void	clean_text(char **splitted);

	//	***NORMINATTE***
int		get_count_x(char *line);
int		get_count_y(int y);
int		norme_norminatte(int first_line, char *line, int fd);
int		check_norme(t_wolf *wolf);

	//	***MAP_READER***
int     **init_map_array(void);
int		*get_array_line(char *line);
void	print_map(t_wolf *wolf);
int		**read_map(t_wolf *wolf);

#endif
