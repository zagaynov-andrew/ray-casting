/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:23:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/28 19:28:38 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <limits.h>
#include "../cub3d.h"

t_vec2f	*init_ray_dir(t_game *game, t_vec2f *ray_dir, int len)
{
	ray_dir->x = len * cos(game->cur_ray_angle);
	ray_dir->y = len * (-sin(game->cur_ray_angle));
	return (ray_dir);
}

int		cut_line(t_game *game, t_vec2f *ray_dir)
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
		side = cut_line(game, &ray_dir);
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

void	game_zero_ptrs(t_game *game)
{
	game->wall_depth = NULL;
	game->angle = NULL;
	game->sprites = NULL;
	game->img.img = NULL;
	game->no.img = NULL;
	game->so.img = NULL;
	game->we.img = NULL;
	game->ea.img = NULL;
	game->s.img = NULL;
	game->win = NULL;
	game->mlx = NULL;
}

void	destroy_mlx_ptrs(t_game *game)
{
	if (game->img.img != NULL)
		mlx_destroy_image(game->mlx, game->img.img);
	if (game->no.img != NULL)
		mlx_destroy_image(game->mlx, game->no.img);
	if (game->so.img != NULL)
		mlx_destroy_image(game->mlx, game->so.img);
	if (game->we.img != NULL)
		mlx_destroy_image(game->mlx, game->we.img);
	if (game->ea.img != NULL)
		mlx_destroy_image(game->mlx, game->ea.img);
	if (game->s.img != NULL)
		mlx_destroy_image(game->mlx, game->s.img);
	if (game->win != NULL)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx != NULL)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
}

int		main(int argc, char **argv)
{
	t_game	game;
	t_scene	*scene;

	if (argc < 2 || argc > 3)
		exit(print_error_string("Error\nInvalid number of arguments\n"));
	if (argc == 3 && ft_strcmp(argv[2], "--save") != 0)
		exit(print_error_string("Error\nInvalid arguments\n"));
	scene = parse_cub(argv[1]);
	if (!scene)
	{
		free_scene(scene);
		exit(print_error());
	}
	game_zero_ptrs(&game);
	if (init_window(&game, scene) == -1)
		exit(print_error_string("Error\nUnable to create an MLX instance\n"));
	if (init_game(&game))
		exit(print_error());
	if (argc == 3 && ft_strcmp(argv[2], "--save") == 0)
		save_bmp(&game);
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.win, 33, 1L << 17, exit_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}
