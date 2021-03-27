/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:23:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 10:29:13 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <limits.h>
#include "../cub3d.h"

int			cut_line(t_game *game, t_vec2f *ray_dir)
{
	t_dda	dda;
	int		side;
	t_vec2	vec2_dir;

	ray_dir->x = RAY_LEN * cos(game->cur_ray_angle);
	ray_dir->y = RAY_LEN * (-sin(game->cur_ray_angle));
	init_dda(&dda, game, ray_dir);
	while (1)
	{
		if (dda.side_dist_x < dda.side_dist_y)
		{
			ray_dir->x = dda.side_dist_x * cos(game->cur_ray_angle);
			ray_dir->y = dda.side_dist_x * (-sin(game->cur_ray_angle));
		}
		else
		{
			ray_dir->x = dda.side_dist_y * cos(game->cur_ray_angle);
			ray_dir->y = dda.side_dist_y * (-sin(game->cur_ray_angle));
		}
		if ((side = is_wall(game, vec2f_to_vec2(&vec2_dir, ray_dir))) != 0)
			return (side);
		if (dda.side_dist_x < dda.side_dist_y)
			dda.side_dist_x += dda.delta_dist_x;
		else
			dda.side_dist_y += dda.delta_dist_y;
	}
	return (side);
}

int				get_texture_offset_x(t_game *game, t_vec2f *ray_dir, int side)
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

void			draw_walls(t_game *game)
{
	int		i;
	int		side;
	t_vec2	info;
	t_vec2	win_point;
	t_vec2f	ray_dir;

	game->cur_ray_angle = game->player.cam_angle + FOV / 2;
	win_point.x = 0;
	win_point.y = game->img.height / 2;
	i = 0;
	while (i < game->scene->width + 1)
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
		i++;
	}
	game->last_side = NOTHING;
}

int				main(int argc, char **argv)
{
	t_game	game;
	t_scene	*scene;

	if (argc < 2 || argc > 3)
		exit(print_error_string("Error\nInvalid number of arguments\n"));
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
		exit(print_error_string("Error\nInvalid arguments\n"));
	scene = parse_cub(argv[1]);
	if (!scene)
	{
		print_error();
		free_scene(scene);
		exit(EXIT_FAILURE);
	}
	if (init_window(&game, scene) == -1)
		exit(print_error_string("Error\nUnable to create an MLX instance\n"));
	init_game(&game);
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
	{
		save_bmp(&game);
		exit_game(&game);
		exit(EXIT_FAILURE);
	}
	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.win, 33, 1L << 17, exit_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	mlx_loop(game.mlx);
}
