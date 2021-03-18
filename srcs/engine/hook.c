/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 11:13:24 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 16:01:45 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		key_pressed(int key_code, t_game *game)
{
	printf("Key pressed: %i!\n", key_code);
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
	printf("Key released: %i!\n", key_code);
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

void	move_straight(t_game *game, int where)
{
	t_vec2	dir;
	t_vec2	*cur_pos;

	dir.x = 6;
	dir.y = 0;
	cur_pos = &game->player->pos;
	rotate(&dir, game->player->cam_angle);
	if (where == TOWARD)
	{
		if (is_wall_around_point(game, cur_pos->x + dir.x, cur_pos->y + dir.y))
			return ;
		cur_pos->x += dir.x;
		cur_pos->y += dir.y;
	}
	else if (where == BACKWARD)
	{
		if (is_wall_around_point(game, cur_pos->x - dir.x, cur_pos->y - dir.y))
			return ;
		cur_pos->x -= dir.x;
		cur_pos->y -= dir.y;
	}
}

void	move_sidewise(t_game *game, int where)
{
	t_vec2	dir;
	t_vec2	*cur_pos;

	dir.x = 6;
	dir.y = 0;
	cur_pos = &game->player->pos;
	rotate(&dir, game->player->cam_angle);
	if (where == LEFT)
	{
		if (is_wall_around_point(game, cur_pos->x + dir.y, cur_pos->y - dir.x))
			return ;
		cur_pos->y -= dir.x;
		cur_pos->x += dir.y;
	}
	else if (where == RIGHT)
	{
		if (is_wall_around_point(game, cur_pos->x - dir.y, cur_pos->y + dir.x))
			return ;
		cur_pos->y += dir.x;
		cur_pos->x -= dir.y;
	}
}

void	move_player(t_game *game)
{
	if (game->player->movement & TOWARD)
		move_straight(game, TOWARD);
	if (game->player->movement & BACKWARD)
		move_straight(game, BACKWARD);
	if (game->player->movement & LEFT)
		move_sidewise(game, LEFT);
	if (game->player->movement & RIGHT)
		move_sidewise(game, RIGHT);
}

void	rotate_player(t_game *game)
{
	if (game->player->rotation & COUNTERCLOCKWISE)
		game->player->cam_angle += 0.05;
	else if (game->player->rotation & CLOCKWISE)
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