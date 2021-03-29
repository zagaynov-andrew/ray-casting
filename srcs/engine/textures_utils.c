/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:23:53 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/29 14:29:46 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		lower_cutoff(t_game *game, float *tex_pos_y, float step, int height)
{
	if (height > game->scene->height)
	{
		*tex_pos_y = step * (height / 2 - game->horizont);
		return (height / 2 - game->horizont);
	}
	return (0);
}

int		upper_cutoff(t_game *game, int height)
{
	int	delta;

	delta = height / 2 - (game->scene->height - game->horizont);
	if (delta < 0)
		delta = 0;
	return (delta);
}

int		get_texture_offset_x(t_game *game, t_vec2f *ray_dir, int side)
{
	int	wall_coord;

	if (side == NO)
	{
		wall_coord = game->player.pos.x + (int)round(ray_dir->x);
		return ((int)((float)(wall_coord % CUB_SIZE) / CUB_SIZE * 64));
	}
	if (side == SO)
	{
		wall_coord = game->player.pos.x + (int)round(ray_dir->x);
		return ((int)((float)(wall_coord % CUB_SIZE) / CUB_SIZE * 64));
	}
	else
	{
		wall_coord = game->player.pos.y + (int)round(ray_dir->y);
		return ((int)((float)(wall_coord % CUB_SIZE) / CUB_SIZE * 64));
	}
}
