/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 17:24:56 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 17:32:49 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	move_straight(t_game *game, int where)
{
	t_vec2	dir;
	t_vec2	*cur_pos;

	dir.x = game->scene->width * 0.02 * MOVEMENT_SPEED;
	dir.y = 0;
	cur_pos = &game->player.pos;
	vec2_rotate(&dir, game->player.cam_angle);
	if (where == TOWARD)
	{
		if (is_barrier_around_point(game, cur_pos->x + dir.x,
											cur_pos->y + dir.y))
			return ;
		cur_pos->x += dir.x;
		cur_pos->y += dir.y;
	}
	else if (where == BACKWARD)
	{
		if (is_barrier_around_point(game, cur_pos->x - dir.x,
											cur_pos->y - dir.y))
			return ;
		cur_pos->x -= dir.x;
		cur_pos->y -= dir.y;
	}
}

void	move_sidewise(t_game *game, int where)
{
	t_vec2	dir;
	t_vec2	*cur_pos;

	dir.x = game->scene->width * 0.02 * MOVEMENT_SPEED;
	dir.y = 0;
	cur_pos = &game->player.pos;
	vec2_rotate(&dir, game->player.cam_angle);
	if (where == LEFT)
	{
		if (is_barrier_around_point(game, cur_pos->x + dir.y,
											cur_pos->y - dir.x))
			return ;
		cur_pos->y -= dir.x;
		cur_pos->x += dir.y;
	}
	else if (where == RIGHT)
	{
		if (is_barrier_around_point(game, cur_pos->x - dir.y,
											cur_pos->y + dir.x))
			return ;
		cur_pos->y += dir.x;
		cur_pos->x -= dir.y;
	}
}

void	move_player(t_game *game)
{
	if (game->player.movement & TOWARD)
		move_straight(game, TOWARD);
	if (game->player.movement & BACKWARD)
		move_straight(game, BACKWARD);
	if (game->player.movement & LEFT)
		move_sidewise(game, LEFT);
	if (game->player.movement & RIGHT)
		move_sidewise(game, RIGHT);
}

void	rotate_player(t_game *game)
{
	if (game->player.rotation & COUNTERCLOCKWISE)
		game->player.cam_angle += game->scene->width * 0.00002 * ROTATION_SPEED;
	if (game->player.rotation & CLOCKWISE)
		game->player.cam_angle -= game->scene->width * 0.00002 * ROTATION_SPEED;
	if (game->player.cam_angle >= 2 * M_PI)
		game->player.cam_angle -= 2 * M_PI;
	if (game->player.cam_angle < 0)
		game->player.cam_angle += 2 * M_PI;
}
