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
	int		red;
	int		green;
	int		blue;

	pix = pixels;
	blue = pix[idx];
	green = pix[idx + 1] << 8;
	red = pix[idx + 2] << 16;
	return (red | green | blue);
}

void	load_texture(t_wolf *wolf, int text_numb, char	*text_path)
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
	if (img = IMG_Load(text_path) == NULL)
		error_exit(LOAD_ERR);
	while (++idx < count_pix)
		pixels[idx] = get_texel(img->pixels, idx * 4)
	SDL_FreeSurface(img);
	wolf->textures[text_numb++] = pixels;

}

void	load_all_textures (t_wolf *wolf)
{
	int		idx;

	idx = -1;
	load_texture(wolf->textures[++idx],"../pic/0.png");
	load_texture(wolf->textures[++idx],"../pic/1.png");
	load_texture(wolf->textures[++idx],"../pic/2.png");
	load_texture(wolf->textures[++idx],"../pic/3.png");
	load_texture(wolf->textures[++idx],"../pic/4.png");
	load_texture(wolf->textures[++idx],"../pic/5.png");
	load_texture(wolf->textures[++idx],"../pic/6.png");
	load_texture(wolf->textures[++idx],"../pic/7.png");
}
