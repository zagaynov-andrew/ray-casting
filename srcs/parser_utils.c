/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 15:20:46 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 22:32:33 by nforce           ###   ########.fr       */
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

int		push_new_map_line(char *line, t_scene *scene)
{
	char	*line_copy;

	if (scene->empty_line == 1)
	{
		errno = 999;
		return (-1);
	}
	if (!(line_copy = ft_strdup(line)))
	{
		errno = 999;
		return (-1);
	}
	if (!ft_vec_push(&(scene->map), (void*)line_copy))
	{
		errno = 999;
		return (-1);
	}
	return (1);
}

int		parse_line_two_letters(char *line, t_scene *scene)
{
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "NO", 2) == 0 && ft_is_whitespace(*(line + 2)))
	{
		if (parse_texture_path(line + 3, &(scene->no)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "SO", 2) == 0 && ft_is_whitespace(*(line + 2)))
	{
		if (parse_texture_path(line + 3, &(scene->so)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "WE", 2) == 0 && ft_is_whitespace(*(line + 2)))
	{
		if (parse_texture_path(line + 3, &(scene->we)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "EA", 2) == 0 && ft_is_whitespace(*(line + 2)))
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
	while (*line == ' ' || *line == '\t')
		line++;
	if (ft_strncmp(line, "R", 1) == 0 && ft_is_whitespace(*(line + 1)))
	{
		if (parse_r(line + 2, scene) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "S", 1) == 0 && ft_is_whitespace(*(line + 1)))
	{
		if (parse_texture_path(line + 2, &(scene->s)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "F", 1) == 0 && ft_is_whitespace(*(line + 1)))
	{
		if (parse_fc(line + 2, &(scene->f)) == -1)
			return (-1);
	}
	else if (ft_strncmp(line, "C", 1) == 0 && ft_is_whitespace(*(line + 1)))
	{
		if (parse_fc(line + 2, &(scene->c)) == -1)
			return (-1);
	}
	else
		return (0);
	return (1);
}
