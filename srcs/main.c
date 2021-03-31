/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:23:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:09:26 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <errno.h>

#include <limits.h>
#include "cub3d.h"

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
