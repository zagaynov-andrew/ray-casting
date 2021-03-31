/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:07:37 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 17:27:24 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_sprite	*create_sprite(int map_x, int map_y)
{
	t_sprite	*spr;

	spr = (t_sprite*)malloc(sizeof(t_sprite));
	if (!spr)
	{
		errno = ENOMEM;
		return (NULL);
	}
	spr->was_visible = 0;
	spr->visible = 0;
	spr->pos.x = map_x * CUB_SIZE + CUB_SIZE / 2;
	spr->pos.y = map_y * CUB_SIZE + CUB_SIZE / 2;
	return (spr);
}

int			init_sprites(t_game *game)
{
	t_sprite	*spr;
	char		*line;
	int			x;
	int			y;

	if (!(game->sprites = ft_vec_new(10)))
		return (-1);
	y = -1;
	while (++y < (int)game->scene->map->size)
	{
		line = (char*)((game->scene->map->data)[y]);
		x = -1;
		while (line[++x])
		{
			if (line[x] == SPRITE)
			{
				if (!(spr = create_sprite(x, y)))
					return (-1);
				if (!ft_vec_push(&game->sprites, spr))
					return (-1);
			}
		}
	}
	return (0);
}

void		draw_sprite(t_game *game, t_sprite *spr, int win_offset_x,
																	int size)
{
	t_vec2	win_point;
	t_vec2	info;
	float	step;
	float	offset;

	win_point.x = win_offset_x;
	win_point.y = game->horizont;
	info.x = 0;
	info.y = size;
	step = (float)game->s.width / size;
	offset = 0;
	while (info.x < game->s.width)
	{
		if (win_point.x >= game->scene->width)
			return ;
		if (win_point.x >= 0)
			if (spr->depth * cos(game->player.cam_angle -
										game->angle[win_point.x]) <
											game->wall_depth[win_point.x])
				draw_texture_line(game, win_point, info, SPRITE);
		offset += step;
		info.x = (int)offset;
		win_point.x++;
	}
}

void		draw_sprites_util(t_game *game)
{
	t_sprite	*spr;
	int			i;
	int			size;
	int			win_offset_x;

	sprites_sort(game->sprites);
	i = game->sprites->size - 1;
	while (i >= 0)
	{
		spr = (t_sprite*)(game->sprites->data[i]);
		if (spr->visible == 1)
		{
			size = ((game->scene->width + 1) / (2 * tan(FOV / 2)) *
												CUB_SIZE / spr->depth);
			win_offset_x = game->img.width / 2 +
					(int)round(spr->delta_angle / FOV * game->img.width) -
																	size / 2;
			draw_sprite(game, spr, win_offset_x, size);
		}
		i--;
	}
}

void		draw_sprites(t_game *game)
{
	set_visible(game);
	draw_sprites_util(game);
}
