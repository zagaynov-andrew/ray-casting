/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:07:37 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/24 15:30:38 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_sprite	*create_sprite(int map_x, int map_y)
{
	t_sprite	*spr;

	spr = (t_sprite*)malloc(sizeof(t_sprite));
	if (!spr)
		return (NULL);
	spr->pos.x = map_x * CUB_SIZE + CUB_SIZE / 2;
	spr->pos.y = map_y * CUB_SIZE + CUB_SIZE / 2;
	return (spr);
}

void		init_sprites(t_game *game)
{
	t_vec		*map;
	t_sprite	*spr;
	char		*line;
	int			x;
	int			y;

	game->sprites = ft_vec_new(10); //
	map = game->scene->map;
	y = 0;
	while (y < (int)map->size)
	{
		line = (char*)((map->data)[y]);
		x = 0;
		while (line[x])
		{
			if (line[x] == SPRITE)
			{
				spr = create_sprite(x, y);
				ft_vec_push(&game->sprites, spr);
			}
			x++;
		}
		y++;
	}
}

void merge(t_vec *A, int p, int q, int r)
{
	int	n1 = q - p;
	int	n2 = r - q;
	int i, j, k;

	t_vec *L = ft_vec_new(n1);
	t_vec *R = ft_vec_new(n2);
    for (i=0; i < n1; i++)
        L->data[i] = A->data[p + i];
    for (j=0; j<n2; j++)
        R->data[j]= A->data[q + j];
    i = 0;
	j = 0;
    for (k = p; k < r; k++)
	{
        if(j >= n2 || (i < n1 && ((t_sprite*)(L->data[i]))->depth <= ((t_sprite*)(R->data[i]))->depth))
            A->data[k] = L->data[i++];
        else
            A->data[k] = R->data[j++];
	}
	ft_vec_free(L);
	ft_vec_free(R);
}

void part(t_vec *A, int p, int r)
{
	int q;
	
    if ((r - p) < 2)
        return;
    q = (p + r) / 2;
    part(A, p, q);
    part(A, q, r);
    merge(A, p, q, r);
}

t_sprite	*sprite_cpy(t_sprite *dst, const t_sprite *src)
{
	vec2_cpy(&dst->pos, &src->pos);
	dst->depth = src->depth;
	dst->delta_angle = src->delta_angle;
	dst->visible = src->visible;
	vec2_cpy(&dst->dir, &src->dir);
	return (dst);
}

void	ft_swap(void *a, void *b)
{
	t_sprite	tmp;

	sprite_cpy(&tmp, (t_sprite*)a);
	sprite_cpy((t_sprite*)a, (t_sprite*)b);
	sprite_cpy((t_sprite*)b, &tmp);
	// tmp = *a;
	// *a = *b;
	// *b = tmp;
}

void			sprites_sort(t_vec *sprites)
{
	int			i;
	int			j;
	void		*tmp;

	i = 0;
	while (i < (int)sprites->size - 1)
	{
		j = 0;
		while (j < (int)sprites->size - i - 1)
		{
			if (((t_sprite*)(sprites->data[j]))->depth >
					((t_sprite*)(sprites->data[j + 1]))->depth)
				// ft_swap(sprites->data[j], sprites->data[j + 1]);
			{
				tmp = sprites->data[j];
				sprites->data[j] = 
						sprites->data[j + 1];
				sprites->data[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void			sprite_set_data(t_game *game)
{
	int			i;
	t_sprite	*spr;
	
	i = 0;
	while (i < (int)game->sprites->size)
	{
		spr = (t_sprite*)(game->sprites->data[i]);
		if (spr->visible == 1)
			spr->depth = vec2_length(&spr->dir);
		i++;
	}
}

void			sprite_delta_angle(t_game *game, t_sprite *spr)
{
	spr->delta_angle = -atan2(spr->dir.y, spr->dir.x);
	if (spr->delta_angle < 0.)
		spr->delta_angle += 2 * M_PI;
	spr->delta_angle = game->player->cam_angle - spr->delta_angle;
	if (spr->delta_angle > M_PI)
		spr->delta_angle = spr->delta_angle - 2 * M_PI;
	if (spr->delta_angle < -M_PI)
		spr->delta_angle += 2 * M_PI;
}

int				min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

void			set_visible(t_game *game)
{
	t_sprite	*spr;
	int			i;

	i = 0;
	while (i < (int)game->sprites->size)
	{
		spr = (t_sprite*)(game->sprites->data[i]);
		spr->dir.x = spr->pos.x - game->player->pos.x;
		spr->dir.y = spr->pos.y - game->player->pos.y;
		sprite_delta_angle(game, spr);
		spr->depth = vec2_length(&spr->dir);
		if ((spr->delta_angle < FOV / 2 + 0.33 && spr->delta_angle > -FOV / 2 - 0.33) &&
				spr->depth > 0.8 *CUB_SIZE)
		{
			spr->visible = 1;
			
		}
		else
			spr->visible = 0;
		i++;
	}
}

void			draw_sprite(t_game *game, t_sprite *spr, int win_offset_x, int size)
{
	t_vec2	win_point;
	t_vec2	info;
	float	step;
	float	offset;

	win_point.x = win_offset_x;
	win_point.y = game->img->height / 2;
	info.x = 0;
	info.y = size;
	step = (float)game->s.width / size;
	offset = 0;
	while (info.x < game->s.width)
	{
		if (spr->depth * cos(game->player->cam_angle - game->angle[win_point.x]) < 
													game->wall_depth[win_point.x])
			draw_texture_line(game, win_point, info, SPRITE);
		offset += step;
		info.x = (int)offset;
		win_point.x++;
	}
}

void			draw_sprites_util(t_game *game)
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
			size = ((game->scene->width + 1) / (2 * tan(FOV / 2)) * CUB_SIZE / spr->depth);
			win_offset_x = game->img->width / 2 + (int)round(spr->delta_angle / FOV * game->img->width) -
				size / 2;
			draw_sprite(game, spr, win_offset_x, size);
		}
		i--;
	}
}

void			draw_sprites(t_game *game)
{
    set_visible(game);
	draw_sprites_util(game);
}