/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 12:07:37 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/23 17:54:56 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void			sprite_set_data(t_game *game)
{
	t_list		*it;
	t_sprite	*spr;
	
	it = game->sprites;
	while (it)
	{
		spr = (t_sprite*)it->content;
		if (spr->visible == 1)
			spr->depth = vec2_length(&spr->dir);
		it = it->next;
	}
}

void			sprite_delta_angle(t_game *game, t_sprite *spr)
{
	spr->delta_angle = -atan2(spr->dir.y, spr->dir.x);
	if (spr->delta_angle < 0.)
		spr->delta_angle += 2 * M_PI;
	spr->delta_angle = game->player->cam_angle - spr->delta_angle;
	if (spr->delta_angle > M_PI)
		spr->delta_angle = fabs(spr->delta_angle - 2 * M_PI);
	if (spr->delta_angle < -M_PI)
		spr->delta_angle += 2 * M_PI;
}

void			set_visible(t_game *game)
{
	t_sprite	*spr;
	t_list		*it;

	it = game->sprites;
	while (it)
	{
		spr = it->content;
		spr->dir.x = spr->pos.x - game->player->pos.x;
		spr->dir.y = spr->pos.y - game->player->pos.y;
		sprite_delta_angle(game, spr);
		if (spr->delta_angle < FOV / 2 + 0.33 && spr->delta_angle > -FOV / 2 - 0.33)
		{
			spr->visible = 1;
			spr->depth = vec2_length(&spr->dir);
			printf("1\n");
		}
		else
		{
			spr->visible = 0;
			printf("0\n");
		}

		it = it->next;
	}
}

void			draw_sprites_util(t_game *game)
{
	t_sprite	*spr;
	t_list		*it;
	t_vec2		p0;
	int			size;

	it = game->sprites;
	while (it)
	{
		spr = it->content;
		if (spr->visible == 1)
		{
			p0.x = game->img->width / 2 + (int)round(spr->delta_angle / FOV * game->img->width);
			p0.y = game->img->height / 2;
			size = ((game->scene->width + 1) / (2 * tan(FOV / 2)) * CUB_SIZE / spr->depth);
			// p0.x = (spr->delta_angle - 
			draw_square_centre(game->img, &p0, size, (((int)sin(spr->depth) * 256) << 16 | (int)(sin(spr->depth) * 256) << 8 | (int)(sin(spr->depth) * 256)));
		}
		it = it->next;
	}
}

void			draw_sprites(t_game *game)
{
    set_visible(game);
	draw_sprites_util(game);
	
}