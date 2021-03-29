/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/28 22:33:17 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/28 22:33:29 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_sprite	*sprite_cpy(t_sprite *dst, const t_sprite *src)
{
	vec2_cpy(&dst->pos, &src->pos);
	dst->depth = src->depth;
	dst->delta_angle = src->delta_angle;
	dst->visible = src->visible;
	vec2_cpy(&dst->dir, &src->dir);
	return (dst);
}

void		sprites_sort(t_vec *sprites)
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

void		sprite_set_data(t_game *game)
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

void		sprite_delta_angle(t_game *game, t_sprite *spr)
{
	spr->delta_angle = -atan2(spr->dir.y, spr->dir.x);
	if (spr->delta_angle < 0.)
		spr->delta_angle += 2 * M_PI;
	spr->delta_angle = game->player.cam_angle - spr->delta_angle;
	if (spr->delta_angle > M_PI)
		spr->delta_angle = spr->delta_angle - 2 * M_PI;
	if (spr->delta_angle < -M_PI)
		spr->delta_angle += 2 * M_PI;
}

void		set_visible(t_game *game)
{
	t_sprite	*spr;
	int			i;

	i = 0;
	while (i < (int)game->sprites->size)
	{
		spr = (t_sprite*)(game->sprites->data[i]);
		spr->dir.x = spr->pos.x - game->player.pos.x;
		spr->dir.y = spr->pos.y - game->player.pos.y;
		sprite_delta_angle(game, spr);
		spr->depth = vec2_length(&spr->dir);
		if ((spr->delta_angle < FOV / 2 + 0.33 && spr->delta_angle >
				-FOV / 2 - 0.33) && spr->depth > 0.8 * CUB_SIZE)
			spr->visible = 1;
		else
			spr->visible = 0;
		i++;
	}
}
