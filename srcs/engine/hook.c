/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:13:24 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/23 14:29:24 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_pressed(int key_code, t_game *game)
{
	if (key_code == KEY_W || key_code == KEY_UP)
		game->player->movement |= TOWARD;
	else if (key_code == KEY_S || key_code == KEY_DOWN)
		game->player->movement |= BACKWARD;
	else if (key_code == KEY_A)
		game->player->movement |= LEFT;
	else if (key_code == KEY_D)
		game->player->movement |= RIGHT;
	else if (key_code == KEY_LEFT)
		game->player->rotation |= COUNTERCLOCKWISE;
	else if (key_code == KEY_RIGHT)
		game->player->rotation |= CLOCKWISE;
	return (0);
}

int		key_released(int key_code, t_game *game)
{
	if (key_code == KEY_W || key_code == KEY_UP)
		game->player->movement &= (0b11111111 - TOWARD);
	else if (key_code == KEY_S || key_code == KEY_DOWN)
		game->player->movement &= (0b11111111 - BACKWARD);
	else if (key_code == KEY_A)
		game->player->movement &= (0b11111111 - LEFT);
	else if (key_code == KEY_D)
		game->player->movement &= (0b11111111 - RIGHT);
	else if (key_code == KEY_LEFT)
		game->player->rotation &= (0b11111111 - COUNTERCLOCKWISE);
	else if (key_code == KEY_RIGHT)
		game->player->rotation &= (0b11111111 - CLOCKWISE);
	if (key_code == KEY_ESC)
		exit_game(game);
	return (0);
}

int		exit_game(t_game *game)
{
	free_scene(game->scene);
	ft_lstclear(&game->sprites, free);
	exit(0);
	return (0);
}

int		render_frame(t_game *game)
{
	move_player(game);
	rotate_player(game);
	// img_clear(game->img);



	t_vec2 begin;
	vec2_init(&begin, 0, 0);
	t_vec2 end;
	vec2_init(&end, game->img->width, game->img->height / 2);
	draw_rectangle(game->img, &begin, &end, 0 << 16 | 186 << 8 | 255);

	vec2_init(&begin, 0, game->img->height / 2);
	vec2_init(&end, game->img->width, game->img->height);
	draw_rectangle(game->img, &begin, &end, 40 << 16 | 40 << 8 | 40);

	// draw_map(game->img, game->scene->map);
	// draw_square_centre(game->img, &game->player->pos, CUB_SIZE, 0x0000FF00);
	draw_rays(game);
	draw_sprites(game);
	// t_vec2 begin;
	// t_vec2 end;
	// begin.x = 1800;
	// begin.y = 442;
	// end.x = 1764;
	// end.y = 458;
	// draw_rectangle(game->img, &begin, &end, 0x00FFFFFF);

	mlx_put_image_to_window(game->mlx, game->win, game->img->img, 0, 0);
	// mlx_put_image_to_window(game->mlx, game->win, img.img, 0, 0);
	return (0);
}
