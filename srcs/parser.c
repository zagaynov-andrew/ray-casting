/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 15:36:19 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 15:48:22 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_scene	*parse_cub(char *path)
{
	t_scene	*scene;
	char	*line;
	int		fd;
	int		gnl_res;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (NULL);
	if (!(scene = scene_new()))
		return (NULL);
	while ((gnl_res = get_next_line(fd, &line)) >= 0)
	{
		if (parse_line(line, scene) == -1)
		{
			free(line);
			free_scene(scene);
			read_remain(fd);
			close(fd);
			return (NULL);
		}
		free(line);
		if (gnl_res == 0)
			break ;
	}
	close(fd);
	return (scene);
}

int		parse_line(char *line, t_scene *scene)
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
	if (parse_map_line(line, scene) != 1)
		return (-1);
	return (1);
}

int		parse_map_line(char *line, t_scene *scene)
{
	if (!is_full_configs(scene))
	{
		errno = 999;
		return (-1);
	}
	else
	{
		if (!is_valid_map_line(line, scene))
			return (-1);
		if (!push_new_map_line(line, scene))
			return (-1);
	}
	return (1);
}

int		parse_line_two_letters(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "NO ", 3) == 0)
	{
		if (parse_texture_path(line + 3, &(scene->no)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "SO ", 3) == 0)
	{
		if (parse_texture_path(line + 3, &(scene->so)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "WE ", 3) == 0)
	{
		if (parse_texture_path(line + 3, &(scene->we)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "EA ", 3) == 0)
	{
		if (parse_texture_path(line + 3, &(scene->ea)) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}

int		parse_line_one_letter(char *line, t_scene *scene)
{
	if (ft_strncmp(line, "R ", 2) == 0)
	{
		if (parse_r(line + 2, scene) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "S ", 2) == 0)
	{
		if (parse_texture_path(line + 2, &(scene->s)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "F ", 2) == 0)
	{
		if (parse_fc(line + 2, &(scene->f)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "C ", 2) == 0)
	{
		if (parse_fc(line + 2, &(scene->c)) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}
