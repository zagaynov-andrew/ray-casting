/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:35 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/22 22:09:48 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void			init_game(t_game *game, t_scene **scene, t_player *player,
																	t_img *img)
{
	game->scene = *scene;
	game->player = player;
	game->img = img;
}

void			init_mlx(t_game *game, void **mlx, void **mlx_win)
{
	game->mlx = *mlx;
	game->win = *mlx_win;
}

void			set_cur_ray_angle(t_game *game, float cur_ray_angle)
{
	game->cur_ray_angle = cur_ray_angle;
	if (game->cur_ray_angle >= 2 * M_PI)
		game->cur_ray_angle -= 2 * M_PI;
	if (game->cur_ray_angle < 0)
		game->cur_ray_angle += 2 * M_PI;
}
