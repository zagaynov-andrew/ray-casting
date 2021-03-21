/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:53 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/21 14:32:30 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void			init_dda(t_dda *dda, const t_game *game, const t_vec2f *ray_dir)
{
	dda->delta_dist_x = get_delta_dist_x(ray_dir);
	dda->side_dist_x = get_side_dist_x(game->player, ray_dir,
													dda->delta_dist_x);
	dda->delta_dist_y = get_delta_dist_y(ray_dir);
	dda->side_dist_y = get_side_dist_y(game->player, ray_dir,
													dda->delta_dist_y);
}

float			get_side_dist_x(const t_player *player, const t_vec2f *ray_dir,
															float delta_dist_x)
{
	int		num_line;
	int		line_x;
	float	similarity_coeff;

	num_line = player->pos.x / CUB_SIZE;
	if (ray_dir->x < 0.)
		num_line++;
	line_x = num_line * CUB_SIZE;
	similarity_coeff = (float)ft_abs(player->pos.x - line_x) / CUB_SIZE;
	return ((1. - similarity_coeff) * delta_dist_x);
}

float			get_side_dist_y(const t_player *player, const t_vec2f *ray_dir,
															float delta_dist_y)
{
	int		num_line;
	int		line_y;
	float	similarity_coeff;

	num_line = player->pos.y / CUB_SIZE;
	if (ray_dir->y < 0.)
		num_line++;
	line_y = num_line * CUB_SIZE;
	similarity_coeff = (float)ft_abs(player->pos.y - line_y) / CUB_SIZE;
	return ((1. - similarity_coeff) * delta_dist_y);
}

float			get_delta_dist_x(const t_vec2f *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + (ray_dir->y * ray_dir->y)
												/ (ray_dir->x * ray_dir->x)));
}

float			get_delta_dist_y(const t_vec2f *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + (ray_dir->x * ray_dir->x)
												/ (ray_dir->y * ray_dir->y)));
}
