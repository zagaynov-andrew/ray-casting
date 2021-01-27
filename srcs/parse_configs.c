/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:08:36 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 15:23:59 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	parse_r(char *str, t_scene *scene)
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
	if (!next_value(&str, scene->width))
		return (-1);
	if ((scene->height = ft_atoi(str)) <= 0)
	{
		errno = 999;
		return (-1);
	}
	if (!next_value(&str, scene->height))
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (1);
	errno = 999;
	return (-1);
}

int	parse_fc(char *str, unsigned int *color)
{
	if (*color != 0x1000000)
	{
		errno = 999;
		return (-1);
	}
	if (color_component(&str, RED, color) == -1)
		return (-1);
	if (*str == ',')
		str++;
	if (color_component(&str, GREEN, color) == -1)
		return (-1);
	if (*str == ',')
		str++;
	if (color_component(&str, BLUE, color) == -1)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (1);
	errno = 999;
	return (-1);
}

int	parse_texture_path(char *str, char **path)
{
	char	*ptr;
	char	*end;

	while (*str == ' ' || *str == '\t')
		str++;
	if (!(ptr = ft_strnstr(str, ".xpm", ft_strlen(str))))
	{
		errno = 999;
		return (-1);
	}
	ptr += 4;
	end = ptr;
	while (*ptr == ' ' || *ptr == '\t')
		ptr++;
	if (!*ptr)
	{
		*end = '\0';
		if ((is_valid_path(str)) == -1)
			return (-1);
		*path = ft_strdup(str);
		return (1);
	}
	errno = 999;
	return (-1);
}
