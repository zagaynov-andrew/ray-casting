/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:35 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 10:42:31 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"


int				init_window(t_game *game, t_scene *scene)
{
	game->scene = scene;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_scene(game->scene);
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, game->scene->width, game->scene->height, "cub3D");
	if (!game->win)
	{
		free_scene(game->scene);
		return (-1);
	}
	game->img.img = mlx_new_image(game->mlx, game->scene->width, game->scene->height);
	game->img.addr = mlx_get_data_addr(game->img.img, &game->img.bits_per_pixel, 
											&game->img.size_line, &game->img.endian);
	game->img.width = game->scene->width;
	game->img.height = game->scene->height;
	return (0);
}

void			cut_angle(float *angle)
{
	if (*angle >= 2 * M_PI)
		*angle -= 2 * M_PI;
	if (*angle < 0)
		*angle += 2 * M_PI;
}

int				init_game(t_game *game)
{
	
	game->last_side = VERTICAL;
	if (!(game->wall_depth = (float*)malloc((game->img.width + 1) * sizeof(float))))
		return (-1);
	game->angle = (float*)malloc((game->img.width + 1) * sizeof(float)); //!!!!!!!!!!!malloc
	init_player(&game->player, game->scene);
	game->player.pos.x = 2801;
	game->player.pos.y = 948;
	game->player.cam_angle = 4.18777275;
	init_sprites(game);
	init_textures(game);
	return (0);
}