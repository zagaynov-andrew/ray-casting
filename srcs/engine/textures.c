/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:31:48 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/22 22:06:00 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char *dst;

	if (x < 0 || y < 0)
		return (0);
	if (x >= img->width || y >= img->height)
		return (0);
	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

t_img			*get_texture(t_game *game, int texture_code)
{
	t_img	*texture;

	if (texture_code == NO)
		texture = &game->no;
	else if (texture_code == SO)
		texture = &game->so;
	else if (texture_code == WE)
		texture = &game->we;
	else if (texture_code == EA)
		texture = &game->ea;
	return (texture);
}

void			draw_texture_line(t_game *game, t_vec2 win_point, t_vec2 info,
															int texture_code)
{
	t_vec2f	tex_pos;
	t_img	*texture;
	int		height;
	float	step;
	int		i;

	tex_pos.x = (float)info.x;
	tex_pos.y = 0;
	height = info.y;
	win_point.y -= height / 2;
	step = (float)CUB_SIZE / height;
	texture = get_texture(game, texture_code);
	i = 0;
	while (i < height)
	{
		pixel_put(game->img, win_point.x, win_point.y + i,
				get_pixel_color(texture, (int)tex_pos.x, (int)tex_pos.y));
		tex_pos.y += step;
		i++;
	}
}

void			init_textures(t_game *game)
{
	game->no.img = mlx_xpm_file_to_image(game->mlx, game->scene->no,
								&game->no.width, &game->no.height);
	game->no.addr = mlx_get_data_addr(game->no.img, &game->no.bits_per_pixel,
								&game->no.size_line, &game->no.endian);
	game->so.img = mlx_xpm_file_to_image(game->mlx, game->scene->so,
								&game->so.width, &game->so.height);
	game->so.addr = mlx_get_data_addr(game->so.img,
		&game->so.bits_per_pixel, &game->so.size_line, &game->so.endian);
	game->we.img = mlx_xpm_file_to_image(game->mlx, game->scene->we,
								&game->we.width, &game->we.height);
	game->we.addr = mlx_get_data_addr(game->we.img,
		&game->we.bits_per_pixel, &game->we.size_line, &game->we.endian);
	game->ea.img = mlx_xpm_file_to_image(game->mlx, game->scene->ea,
								&game->ea.width, &game->ea.height);
	game->ea.addr = mlx_get_data_addr(game->ea.img,
		&game->ea.bits_per_pixel, &game->ea.size_line, &game->ea.endian);
}
