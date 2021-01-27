/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:36:34 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 15:23:50 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_map_chars(char **line, t_scene *scene)
{
	while (**line && ft_char_in_set(MAP_SET, **line))
	{
		if (ft_char_in_set("NSEW", **line))
		{
			if (scene->start_pos)
			{
				errno = 999;
				return (0);
			}
			scene->start_pos = 1;
		}
		(*line)++;
	}
	return (1);
}

int			is_valid_map_line(char *line, t_scene *scene)
{
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (!*line)
			return (1);
		if (*line != WALL)
		{
			errno = 999;
			return (0);
		}
		if (!check_map_chars(&line, scene))
			return (0);
		if (*(line - 1) != WALL)
		{
			errno = 999;
			return (0);
		}
	}
	return (1);
}
