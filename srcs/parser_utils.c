/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:20:46 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 15:24:02 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int		is_full_configs(t_scene *scene)
{
	if (!scene)
		return (-1);
	if (scene->width == -1)
		return (0);
	if (scene->height == -1)
		return (0);
	if (scene->f == 0x1000000)
		return (0);
	if (scene->c == 0x1000000)
		return (0);
	if (scene->s == NULL)
		return (0);
	if (scene->no == NULL)
		return (0);
	if (scene->so == NULL)
		return (0);
	if (scene->we == NULL)
		return (0);
	if (scene->ea == NULL)
		return (0);
	return (1);
}

void	read_remain(int fd)
{
	char	*line;
	int		gnl_res;

	while ((gnl_res = get_next_line(fd, &line)) >= 0)
	{
		free(line);
		if (gnl_res == 0)
			break ;
	}
}
