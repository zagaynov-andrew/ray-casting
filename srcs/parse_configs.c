/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:08:36 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 22:47:09 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			parse_r(char *str, t_scene *scene)
{
	if (scene->width > 0 || scene->height > 0)
	{
		errno = 999;
		return (-1);
	}
	if ((scene->width = ft_atoi(str)) <= 0)
	{
		errno = 999;
		return (-1);
	}
	if (next_value(&str, scene->width) == -1)
		return (-1);
	if ((scene->height = ft_atoi(str)) <= 0)
	{
		errno = 999;
		return (-1);
	}
	if (next_value(&str, scene->height) == -1)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (1);
	errno = 999;
	return (-1);
}

static int	parse_fc_main(char **str, unsigned int *color)
{
	if (color_component(str, RED, color) == -1)
		return (-1);
	while (ft_is_whitespace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	else
	{
		errno = 999;
		return (-1);
	}
	if (color_component(str, GREEN, color) == -1)
		return (-1);
	while (ft_is_whitespace(**str))
		(*str)++;
	if (**str == ',')
		(*str)++;
	else
	{
		errno = 999;
		return (-1);
	}
	if (color_component(str, BLUE, color) == -1)
		return (-1);
	return (1);
}

int			parse_fc(char *str, unsigned int *color)
{
	if (*color != 0x1000000)
	{
		errno = 999;
		return (-1);
	}
	if (parse_fc_main(&str, color) == -1)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (1);
	errno = 999;
	return (-1);
}

static int	parse_after_texture_path(char *begin, char *after, char **path)
{
	char	*end;

	end = after;
	while (*after == ' ' || *after == '\t')
		after++;
	if (!*after)
	{
		*end = '\0';
		if ((is_valid_path(begin)) == -1)
			return (-1);
		*path = ft_strdup(begin);
		return (1);
	}
	errno = 999;
	return (-1);
}

int			parse_texture_path(char *str, char **path)
{
	char	*ptr;

	if (*path)
	{
		errno = 999;
		return (-1);
	}
	while (*str == ' ' || *str == '\t')
		str++;
	if (!(ptr = ft_strnstr(str, ".xpm", ft_strlen(str))))
	{
		errno = 999;
		return (-1);
	}
	ptr += 4;
	return (parse_after_texture_path(str, ptr, path));
}
