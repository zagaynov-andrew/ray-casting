/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:36:19 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 21:45:17 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_map_line(char *line, t_scene *scene)
{
	if (is_full_configs(scene) != 1)
	{
		errno = 999;
		return (-1);
	}
	else
	{
		if (is_valid_map_row(line, scene) == 0)
			return (-1);
		if (push_new_map_line(line, scene) == -1)
			return (-1);
	}
	return (1);
}

static int	parse_line(char *line, t_scene *scene)
{
	int		res;
	char	*tmp;

	if ((res = parse_line_one_letter(line, scene)) != 0)
		return (res);
	res = parse_line_two_letters(line, scene);
	if (res != 0)
		return (res);
	tmp = line;
	while (*tmp == ' ' || *tmp == '\t')
		tmp++;
	if (!*tmp)
	{
		if (scene->map->size != 0)
			scene->empty_line = 1;
		return (1);
	}
	if (parse_map_line(line, scene) == -1)
		return (-1);
	return (1);
}

static int	parse_cub_main(t_scene **scene, int fd)
{
	char	*line;
	int		gnl_res;

	while ((gnl_res = get_next_line(fd, &line)) >= 0)
	{
		if (parse_line(line, *scene) == -1)
		{
			free(line);
			free_scene(*scene);
			read_remain(fd);
			close(fd);
			return (0);
		}
		free(line);
		if (gnl_res == 0)
			break ;
	}
	return (1);
}

t_scene		*parse_cub(char *path)
{
	t_scene	*scene;
	int		fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (!(scene = scene_new()))
		return (NULL);
	if (parse_cub_main(&scene, fd) == 0)
		return (NULL);
	close(fd);
	if (scene->start_pos == 0)
	{
		free_scene(scene);
		errno = 999;
		return (NULL);
	}
	if (is_valid_map_column(scene->map) != 1)
	{
		free_scene(scene);
		return (NULL);
	}
	return (scene);
}
