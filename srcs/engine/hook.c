/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:13:24 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 09:29:06 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_pressed(int key_code, t_game *game)
{
	if (key_code == KEY_W || key_code == KEY_UP)
		game->player.movement |= TOWARD;
	else if (key_code == KEY_S || key_code == KEY_DOWN)
		game->player.movement |= BACKWARD;
	else if (key_code == KEY_A)
		game->player.movement |= LEFT;
	else if (key_code == KEY_D)
		game->player.movement |= RIGHT;
	else if (key_code == KEY_LEFT)
		game->player.rotation |= COUNTERCLOCKWISE;
	else if (key_code == KEY_RIGHT)
		game->player.rotation |= CLOCKWISE;
	return (0);
}

int		key_released(int key_code, t_game *game)
{
	if (key_code == KEY_W || key_code == KEY_UP)
		game->player.movement &= (0b11111111 - TOWARD);
	else if (key_code == KEY_S || key_code == KEY_DOWN)
		game->player.movement &= (0b11111111 - BACKWARD);
	else if (key_code == KEY_A)
		game->player.movement &= (0b11111111 - LEFT);
	else if (key_code == KEY_D)
		game->player.movement &= (0b11111111 - RIGHT);
	else if (key_code == KEY_LEFT)
		game->player.rotation &= (0b11111111 - COUNTERCLOCKWISE);
	else if (key_code == KEY_RIGHT)
		game->player.rotation &= (0b11111111 - CLOCKWISE);
	if (key_code == KEY_ESC)
		exit_game(game);
	return (0);
}

int		exit_game(t_game *game)
{
	free_scene(game->scene);
	ft_vec_free(game->sprites);
	free(game->wall_depth);
	free(game->angle);
	exit(0);
	return (0);
}

int		render_frame(t_game *game)
{
	move_player(game);
	rotate_player(game);
	draw_floor(game);
	draw_ceiling(game);
	draw_walls(game);
	draw_sprites(game);
	mlx_put_image_to_window(game->mlx, game->win, game->img.img, 0, 0);
	return (0);
}
