/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   side.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/20 09:34:22 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/21 17:27:13 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int		is_wall_no_epsilon(t_game *game, int x, int y)
{
	t_vec	*map;
	char	*line;

	map = game->scene->map;
	line = (char*)((map->data)[y / CUB_SIZE]);
	if (line[x / CUB_SIZE] == WALL)
		return (1);
	return (-1);
}

int	is_vertical(t_game *game, t_vec2 *point)
{
	int	count;

	count = 0;
	if (is_wall_no_epsilon(game, point->x + 2, point->y + 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x - 2, point->y + 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x - 2, point->y - 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x + 2, point->y - 2) == 1)
		count++;
	if (count == 2)
		if (is_wall_no_epsilon(game, point->x - 2, point->y + 2) ==
				is_wall_no_epsilon(game, point->x - 2, point->y - 2))
			return (1);
	return (0);
}

int	is_corner(t_game *game, t_vec2 *point)
{
	int	count;

	count = 0;
	if (is_wall_no_epsilon(game, point->x + 2, point->y + 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x - 2, point->y + 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x - 2, point->y - 2) == 1)
		count++;
	if (is_wall_no_epsilon(game, point->x + 2, point->y - 2) == 1)
		count++;
	if (count == 1)
		return (1);
	return (0);
}

int	is_left_down_corner(t_game *game, t_vec2 *point)
{
	if (is_corner(game, point) == 1 &&
			is_wall_no_epsilon(game, point->x - 2, point->y + 2) == 1)
		return (1);
	return (0);
}

int	is_right_down_corner(t_game *game, t_vec2 *point)
{
	if (is_corner(game, point) == 1 &&
			is_wall_no_epsilon(game, point->x + 2, point->y + 2) == 1)
		return (1);
	return (0);
}

int	is_right_up_corner(t_game *game, t_vec2 *point)
{
	if (is_corner(game, point) == 1 &&
			is_wall_no_epsilon(game, point->x + 2, point->y - 2) == 1)
		return (1);
	return (0);
}

int	is_left_up_corner(t_game *game, t_vec2 *point)
{
	if (is_corner(game, point) == 1 &&
			is_wall_no_epsilon(game, point->x - 2, point->y - 2) == 1)
		return (1);
	return (0);
}

int	check_corner(t_game *game, t_vec2 *point)
{
	if (is_left_down_corner(game, point) == 1)
		if (3 * M_PI_2 < game->cur_ray_angle && game->cur_ray_angle < 2 * M_PI)
			return (HORIZONTAL);
	if (is_right_down_corner(game, point) == 1)
		if (0 < game->cur_ray_angle && game->cur_ray_angle < M_PI_2)
			return (VERTICAL);
	if (is_right_up_corner(game, point) == 1)
		if (M_PI_2 < game->cur_ray_angle && game->cur_ray_angle < M_PI)
			return (HORIZONTAL);
	if (is_left_up_corner(game, point) == 1)
		if (M_PI < game->cur_ray_angle && game->cur_ray_angle < 3 * M_PI_2)
			return (VERTICAL);
	// if (is_vertical(game, point) == 1)
	// 	return (VERTICAL);
	// return (HORIZONTAL);
	return (NOTHING);
}

// static	int	get_line_direction(t_game *game, t_vec2 *point)
// {
// 	if (game->last_side == NOTHING && is_vertical(game, point) == 1)
// 		return (VERTICAL);
// 	if (point->x % CUB_SIZE == 0 && point->y % CUB_SIZE == 0)
// 	{
// 		int	chk_corner;
// 		if ((chk_corner = check_corner(game, point)) != NOTHING)
// 			return (chk_corner);
// 		return (game->last_side);
// 	}
// 	if (point->x % CUB_SIZE == 0)
// 	{
// 		int	chk_corner;
// 		if ((chk_corner = check_corner(game, point)) != NOTHING)
// 			return (chk_corner);
// 		if (((float)(point->y % CUB_SIZE)) / CUB_SIZE > 0.98 &&
// 						game->last_side == HORIZONTAL)
// 		{
// 			return (HORIZONTAL);
// 		}
// 		return (VERTICAL);
// 	}
// 	if (point->y % CUB_SIZE == 0)
// 	{
// 		int	chk_corner;
// 		if ((chk_corner = check_corner(game, point)) != NOTHING)
// 			return (chk_corner);
// 		if (((float)(point->x % CUB_SIZE)) / CUB_SIZE > 0.98 &&
// 						game->last_side == VERTICAL)
// 		{
// 			return (VERTICAL);
// 		}
// 		return (HORIZONTAL);
// 	}
// 	return (NOTHING);
// }

static	int	get_line_direction(t_game *game, t_vec2 *point)
{
	if (is_vertical(game, point) == 1)
		return (VERTICAL);
	return (HORIZONTAL);
}

int			get_side(t_game *game, t_vec2 *point)
{
	float	angle;
	int		dir;

	angle = game->cur_ray_angle;
	dir = get_line_direction(game, point);
	game->last_side = dir;
	if (dir == HORIZONTAL)
	{
		if (0 < angle && angle < M_PI)
			return (NO);
		if (M_PI < angle && angle < 2 * M_PI)
			return (SO);
	}
	if (dir == VERTICAL)
	{
		if (M_PI_2 < angle && angle < 3 * M_PI_2)
			return (WE);
		if ((0 <= angle && angle < M_PI_2) ||
				(3 * M_PI_2 < angle && angle < 2 * M_PI))
			return (EA);
	}
	return (NOTHING);
}
