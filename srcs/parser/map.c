/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 12:36:34 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:06:11 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	check_map_chars(char **line, t_scene *scene)
{
	if (!ft_char_in_set(MAP_SET, **line))
	{
		errno = ERR_EXTRA_MAP;
		return (0);
	}
	while (**line && ft_char_in_set(MAP_SET, **line))
	{
		if (ft_char_in_set("NSEW", **line))
		{
			if (scene->start_pos_flag != ' ')
			{
				errno = ERR_REP_START_POS;
				return (0);
			}
			scene->start_pos_flag = **line;
		}
		(*line)++;
		if (!ft_char_in_set(MAP_SET, **line) && **line && **line != ' ')
		{
			errno = ERR_EXTRA_MAP;
			return (0);
		}
	}
	return (1);
}

int			is_valid_map_row(char *line, t_scene *scene)
{
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (!*line)
			return (1);
		if (*line != WALL)
		{
			errno = (!ft_char_in_set(MAP_SET, *line)) ?
								ERR_EXTRA_MAP : ERR_NO_WALL;
			return (0);
		}
		if (!check_map_chars(&line, scene))
			return (0);
		if (*(line - 1) != WALL)
		{
			errno = ERR_NO_WALL;
			return (0);
		}
	}
	return (1);
}

static int	is_valid_map_column_main(t_vec *map, int column)
{
	char	**array;
	int		i;

	array = (char**)map->data;
	i = 0;
	while (i < (int)map->size)
	{
		while (i < (int)map->size && array[i][column] == ' ')
			i++;
		if (i == (int)map->size)
			return (1);
		if (array[i][column] != WALL)
		{
			errno = ERR_NO_WALL;
			return (0);
		}
		while (i < (int)map->size && ft_char_in_set(MAP_SET, array[i][column]))
			i++;
		if (array[i - 1][column] != WALL)
		{
			errno = ERR_NO_WALL;
			return (0);
		}
	}
	return (1);
}

int			is_valid_map_column(t_vec *map)
{
	t_vec	*tmp;
	int		column;
	int		max_column;

	if (!(tmp = get_rectangular_map(map)))
		return (-1);
	max_column = ft_strlen((char*)((tmp->data)[0]));
	column = 0;
	while (column < max_column)
	{
		if (is_valid_map_column_main(tmp, column) == 0)
		{
			ft_vec_free(tmp);
			return (0);
		}
		column++;
	}
	ft_vec_free(tmp);
	return (1);
}
