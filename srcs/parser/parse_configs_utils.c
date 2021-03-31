/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:40:02 by nforce            #+#    #+#             */
/*   Updated: 2021/03/31 15:06:13 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			is_valid_path(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		errno = ERR_TEXTURE_NOT_EXIST;
		return (-1);
	}
	close(fd);
	return (1);
}

int			next_value(char **str)
{
	pass_whitespaces(str);
	if (!**str)
	{
		errno = ERR_EXTRA_CHAR;
		return (-1);
	}
	if (**str == '-')
		(*str)++;
	while (ft_isdigit(**str) == 1)
		(*str)++;
	return (1);
}

static int	get_color(unsigned int *color, int component, int value)
{
	if (value < 0 || value > 255)
	{
		errno = ERR_INVALID_COLOR;
		return (-1);
	}
	if (!color)
		return (-1);
	if (*color == 0x1000000)
		*color = 0;
	if (component == RED)
		*color += 65536 * value;
	else if (component == GREEN)
		*color += 256 * value;
	else if (component == BLUE)
		*color += value;
	else
		return (-1);
	return (1);
}

int			color_component(char **str, int component, unsigned int *color)
{
	int	value;

	if (*pass_whitespaces(str) == 0)
	{
		errno = ERR_NO_COLOR;
		return (-1);
	}
	value = ft_atoi(*str);
	if (value < 0 || value > 255 || check_int_overflow(*str) > 0)
	{
		errno = ERR_INVALID_COLOR;
		return (-1);
	}
	if (next_value(str) == -1)
		return (-1);
	if (!ft_isdigit(*(*str - 1)))
	{
		errno = ERR_EXTRA_CHAR;
		return (-1);
	}
	if (get_color(color, component, value) == -1)
		return (-1);
	return (1);
}

char		*pass_whitespaces(char **str)
{
	if (!str)
		return (NULL);
	if (!*str)
		return (NULL);
	while (ft_is_whitespace(**str))
		(*str)++;
	return (*str);
}
