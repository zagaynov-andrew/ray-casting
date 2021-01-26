/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 14:40:02 by nforce            #+#    #+#             */
/*   Updated: 2021/01/26 16:15:28 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_valid_path(char *path)
{
	int	fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		errno = 999;
		return (-1);
	}
	close(fd);
	return (1);
}

int	next_value(char **str, int value)
{
	while (**str && !ft_isdigit(**str) && **str != '-')
		(*str)++;
	if (!**str)
	{
		errno = 999;
		return (-1);
	}
	*str += ft_lli_len((int)value);
}

int	color_component(char **str, int component, int *color)
{
	int	value;

	value = ft_atoi(*str);
	if (value < 0 || value > 255)
	{
		errno = 999;
		return (-1);
	}
	if (!next_value(str, value))
		return (-1);
	if (!ft_isdigit(*(*str - 1)))
	{
		errno = 999;
		return (-1);
	}
	if (!get_color(color, component, value))
		return (-1);
	return (1);
}

int	get_color(unsigned int *color, int component, int value)
{
	if (value < 0 || value > 255)
	{
		errno = 999;
		return (-1);
	}
	if (!color)
	{
		errno = 999;
		return (-1);
	}
	if (*color == 0x1000000)
		*color = 0;
	if (component == RED)
		*color += 65536 * value;
	else if (component == GREEN)
		*color += 256 * value;
	else if (component == BLUE)
		*color += value;
	else
	{
		errno = 999;
		return (-1);
	}
	return (1);
}
