/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:13:24 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 23:08:20 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_pressed(int key_code, t_game *game)
{
	// printf("Key pressed: %i!\n", key_code);
	if (key_code == 119)
		game->player->movement |= TOWARD;
	else if (key_code == 115)
		game->player->movement |= BACKWARD;
	else if (key_code == 97)
		game->player->movement |= LEFT;
	else if (key_code == 100)
		game->player->movement |= RIGHT;
	else if (key_code == 65361)
		game->player->rotation |= COUNTERCLOCKWISE;
	else if (key_code == 65363)
		game->player->rotation |= CLOCKWISE;
	return (0);
}

int		key_released(int key_code, t_game *game)
{
	// printf("Key released: %i!\n", key_code);
	if (key_code == 119)
		game->player->movement &= (0b11111111 - TOWARD);
	else if (key_code == 115)
		game->player->movement &= (0b11111111 - BACKWARD);
	else if (key_code == 97)
		game->player->movement &= (0b11111111 - LEFT);
	else if (key_code == 100)
		game->player->movement &= (0b11111111 - RIGHT);
	else if (key_code == 65361)
		game->player->rotation &= (0b11111111 - COUNTERCLOCKWISE);
	else if (key_code == 65363)
		game->player->rotation &= (0b11111111 - CLOCKWISE);
	if (key_code == 65307)
	{
		free_scene(game->scene);
		exit(0);
	}
	return (0);
}

int		render_frame(t_game *game)
{
	move_player(game);
	rotate_player(game);
	img_clear(game->img);
	draw_map(game->img, game->scene->map);
	draw_square_centre(game->img, &game->player->pos, CUB_SIZE, 0x0000FF00);
	draw_rays(game);
	// t_vec2 begin;
	// t_vec2 end;
	// begin.x = 1800;
	// begin.y = 442;
	// end.x = 1764;
	// end.y = 458;
	// draw_rectangle(game->img, &begin, &end, 0x00FFFFFF);
	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	return (0);
}