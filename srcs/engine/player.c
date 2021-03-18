/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:45:09 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 10:45:40 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void				set_start_position(t_player *player, t_vec *map)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < (int)map->size)
	{
		line = (char*)((map->data)[y]);
		x = 0;
		while (line[x])
		{
			if (ft_char_in_set("NSEW", line[x]))
			{
				player->pos.x = x * CUB_SIZE + CUB_SIZE / 2;
				player->pos.y = y * CUB_SIZE + CUB_SIZE / 2;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_scene *scene)
{
	set_start_position(player, scene->map);
	if (scene->start_pos_flag == 'N')
		player->cam_angle = M_PI_2;
	else if (scene->start_pos_flag == 'S')
		player->cam_angle = 3 * M_PI_2;
	else if (scene->start_pos_flag == 'E')
		player->cam_angle = 0;
	else if (scene->start_pos_flag == 'W')
		player->cam_angle = M_PI;

}