/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_corner.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 13:14:11 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 13:20:11 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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
