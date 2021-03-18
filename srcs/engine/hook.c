/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:13:24 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 14:38:40 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_pressed(int key_code, t_game *game)
{
	printf("Key pressed: %i!\n", key_code);
	if (key_code == 119)
		game->player->movement = TOWARD;
	else if (key_code == 115)
		game->player->movement = BACKWARD;
	else if (key_code == 97)
		game->player->movement = LEFT;
	else if (key_code == 100)
		game->player->movement = RIGHT;
	else if (key_code == 65361)
		game->player->rotation = COUNTERCLOCKWISE;
	else if (key_code == 65363)
		game->player->rotation = CLOCKWISE;
	return (0);
}

int		key_released(int key_code, t_game *game)
{
	printf("Key released: %i!\n", key_code);
	if (key_code == 119)
		game->player->movement = STOP;
	else if (key_code == 115)
		game->player->movement = STOP;
	else if (key_code == 97)
		game->player->movement = STOP;
	else if (key_code == 100)
		game->player->movement = STOP;
	else if (key_code == 65361 || key_code == 65363)
		game->player->rotation = STOP;
	if (key_code == 65307)
	{
		free_scene(game->scene);
		exit(0);
	}
	return (0);
}

void	move_player(t_game *game)
{
	if (game->player->movement == TOWARD)
	{
		if (!is_wall_around_point(game, game->player->pos.x, game->player->pos.y - 1))
			game->player->pos.y -= 1;
	}
	else if (game->player->movement == BACKWARD)
	{
		if (!is_wall_around_point(game, game->player->pos.x, game->player->pos.y + 1))
		game->player->pos.y += 1;
	}
	else if (game->player->movement == LEFT)
	{
		if (!is_wall_around_point(game, game->player->pos.x - 1, game->player->pos.y))
		game->player->pos.x -= 1;
	}
	else if (game->player->movement == RIGHT)
	{
		if (!is_wall_around_point(game, game->player->pos.x + 1, game->player->pos.y))
		game->player->pos.x += 1;
	}
}

void	rotate_player(t_game *game)
{
	if (game->player->rotation == COUNTERCLOCKWISE)
		game->player->cam_angle += 0.05;
	else if (game->player->rotation == CLOCKWISE)
		game->player->cam_angle -= 0.05;
}

int		render_frame(t_game *game)
{
	move_player(game);
	rotate_player(game);
	img_clear(game->img);
	draw_map(game->img, game->scene->map);
	draw_square_centre(game->img, &game->player->pos, CUB_SIZE, 0x0000FF00);
	draw_rays(game, 0x0000FFFF);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}