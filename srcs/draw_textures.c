/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dshereme <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/05 20:27:07 by dshereme          #+#    #+#             */
/*   Updated: 2019/07/05 20:27:20 by dshereme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/wolf.h"

int		get_textures_pix_count(void)
{
	int		text_height;
	int		text_width;

	text_height = TEXTURES_H;
	text_width = TEXTURES_W;
	return (text_height * text_width);
}

int		get_texel(void *pixels, int idx) //get_color_pix
{
	char	*pix;
	unsigned	int		red;
	unsigned	int		green;
	unsigned	int		blue;

	pix = pixels;
	blue = pix[idx];
	green = pix[idx + 1] << 8;
	red = pix[idx + 2] << 16;
	return (red | green | blue);
}

void	load_texture(t_wolf *wolf, char	*text_path)
{
	static	int		texture_numb;
	SDL_Surface		*img;
	int				count_pix;
	int				*pixels;
	int				idx;

	count_pix = get_textures_pix_count();
	idx = -1;
	if(!(pixels = (int*)ft_memalloc(sizeof(int) * count_pix)))
		error_exit(MEM_ERR);
	img = SDL_LoadBMP(text_path);
	if (img == NULL)
		error_exit(LOAD_ERR);
	while (++idx < count_pix)
		pixels[idx] = get_texel(img->pixels, idx * 4);
	wolf->textures[texture_numb++] = pixels;
	SDL_FreeSurface(img); //lSDL

}

void	load_all_textures (t_wolf *wolf)
{
//	load_texture(wolf, "../bluestone/witcher.bmp");
	load_texture(wolf, "./bluestone/colorstone.bmp");
	load_texture(wolf, "./bluestone/bluestone.bmp");
	load_texture(wolf, "./bluestone/eagle.bmp");
	load_texture(wolf, "./bluestone/greystone.bmp");
	load_texture(wolf, "./bluestone/mossy.bmp");
	load_texture(wolf, "./bluestone/redbrick.bmp");
	load_texture(wolf, "./bluestone/wood.bmp");
	// load_texture(wolf, "../pic/0.png");
	// load_texture(wolf, "../pic/1.png");
	// load_texture(wolf, "../pic/2.png");
	// load_texture(wolf, "../pic/3.png");
	// load_texture(wolf, "../pic/4.png");
	// load_texture(wolf,"../pic/5.png");
	// load_texture(wolf, "../pic/6.png");
	// load_texture(wolf, "../pic/7.png");
}
