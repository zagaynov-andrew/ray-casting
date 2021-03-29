/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/29 14:26:01 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/29 14:27:51 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_vec2f	*init_ray_dir(t_game *game, t_vec2f *ray_dir, int len)
{
	ray_dir->x = len * cos(game->cur_ray_angle);
	ray_dir->y = len * (-sin(game->cur_ray_angle));
	return (ray_dir);
}

int		get_ray_dir(t_game *game, t_vec2f *ray_dir)
{
	t_dda	dda;
	int		side;
	t_vec2	vec2_dir;

	init_ray_dir(game, ray_dir, RAY_LEN);
	init_dda(&dda, game, ray_dir);
	while (1)
	{
		if (dda.side_dist_x < dda.side_dist_y)
			init_ray_dir(game, ray_dir, dda.side_dist_x);
		else
			init_ray_dir(game, ray_dir, dda.side_dist_y);
		if ((side = is_wall(game, vec2f_to_vec2(&vec2_dir, ray_dir))) != 0)
			return (side);
		if (dda.side_dist_x < dda.side_dist_y)
			dda.side_dist_x += dda.delta_dist_x;
		else
			dda.side_dist_y += dda.delta_dist_y;
	}
	return (side);
}

void	draw_walls(t_game *game)
{
	int		i;
	int		side;
	t_vec2	info;
	t_vec2	win_point;
	t_vec2f	ray_dir;

	game->cur_ray_angle = game->player.cam_angle + FOV / 2;
	win_point.x = 0;
	win_point.y = game->img.height / 2;
	i = -1;
	while (++i < game->scene->width + 1)
	{
		cut_angle(&game->cur_ray_angle);
		side = get_ray_dir(game, &ray_dir);
		game->wall_depth[i] = round((float)vec2f_length(&ray_dir) *
							cos(game->player.cam_angle - game->cur_ray_angle));
		game->angle[i] = game->cur_ray_angle;
		info.x = get_texture_offset_x(game, &ray_dir, side);
		info.y = ((game->scene->width + 1) / (2 * tan(FOV / 2)) * CUB_SIZE /
														game->wall_depth[i]);
		if (side != NOTHING)
			draw_texture_line(game, win_point, info, side);
		win_point.x++;
		game->cur_ray_angle -= FOV / game->scene->width;
	}
}
