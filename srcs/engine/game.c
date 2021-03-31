/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:36:35 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:05:22 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int				init_window(t_game *game, t_scene *scene)
{
	game->scene = scene;
	game->mlx = mlx_init();
	if (!game->mlx)
	{
		free_game(game);
		return (-1);
	}
	game->win = mlx_new_window(game->mlx, game->scene->width,
											game->scene->height, "cub3D");
	game->img.img = mlx_new_image(game->mlx, game->scene->width,
														game->scene->height);
	game->img.addr = mlx_get_data_addr(game->img.img,
			&game->img.bits_per_pixel, &game->img.size_line, &game->img.endian);
	if (!game->win || !game->img.img || !game->img.addr)
	{
		free_game(game);
		return (-1);
	}
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

void			free_game(t_game *game)
{
	free_scene(game->scene);
	if (game->wall_depth != NULL)
		free(game->wall_depth);
	if (game->angle != NULL)
		free(game->angle);
	if (game->sprites != NULL)
		free(game->sprites);
	destroy_mlx_ptrs(game);
}

int				init_game(t_game *game)
{
	game->wall_depth = (float*)malloc((game->img.width + 1) * sizeof(float));
	game->angle = (float*)malloc((game->img.width + 1) * sizeof(float));
	if (!game->wall_depth || !game->angle)
	{
		errno = ENOMEM;
		free_game(game);
		return (-1);
	}
	game->horizont = game->scene->height / 2;
	init_player(&game->player, game->scene);
	if (init_sprites(game) == -1)
	{
		free_game(game);
		return (-1);
	}
	init_textures(game);
	return (0);
}
