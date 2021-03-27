/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_wall.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:10:07 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 10:36:20 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

int	is_wall_around_point(t_game *game, int x, int y)
{
	t_vec	*map;
	char	*line;
	t_vec2	cur;
	t_vec2	begin;

	cur.x = x - EPSILON;
	cur.y = y - EPSILON;
	vec2_cpy(&begin, &cur);
	map = game->scene->map;
	while (cur.y < begin.y + 2 * EPSILON + 1)
	{
		cur.x = begin.x;
		while (cur.x < begin.x + 2 * EPSILON + 1)
		{
			line = (char*)((map->data)[cur.y / CUB_SIZE]);
			if (line[cur.x / CUB_SIZE] == WALL)
				return (1);
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

int	is_wall(t_game *game, t_vec2 *ray_dir)
{
	char	*line;
	t_vec2	cur;
	t_vec2	begin;
	int		flag;

	flag = 0;
	cur.x = game->player.pos.x + ray_dir->x - 2;
	cur.y = game->player.pos.y + ray_dir->y - 2;
	vec2_cpy(&begin, &cur);
	while (cur.y < begin.y + 5)
	{
		cur.x = begin.x;
		while (cur.x < begin.x + 5)
		{
			line = (char*)((game->scene->map->data)[cur.y / CUB_SIZE]);
			if (line[cur.x / CUB_SIZE] == WALL)
				flag = 1;
			if ((cur.x % CUB_SIZE == 0 || cur.y % CUB_SIZE == 0) && flag == 1)
				return (get_side(game, &cur));
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

int	is_wall_no_epsilon(t_game *game, int x, int y)
{
	t_vec	*map;
	char	*line;

	map = game->scene->map;
	line = (char*)((map->data)[y / CUB_SIZE]);
	if (line[x / CUB_SIZE] == WALL)
		return (1);
	return (-1);
}
