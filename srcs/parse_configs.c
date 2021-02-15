/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:08:36 by nforce            #+#    #+#             */
/*   Updated: 2021/01/29 18:38:26 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			parse_r(char *str, t_scene *scene)
{
	if (scene->width > 0 || scene->height > 0)
	{
		errno = ERR_RE_CONFIG;
		return (-1);
	}
	if ((scene->width = ft_atoi(str)) <= 0)
	{
		errno = ERR_RSOLUTION;
		return (-1);
	}
	if (next_value(&str, scene->width) == -1)
		return (-1);
	if (!ft_isdigit(*pass_whitespaces(&str)))
	{
		errno = ERR_EXTRA_CHAR;
		return (-1);
	}
	if ((scene->height = ft_atoi(str)) <= 0)
	{
		errno = ERR_RSOLUTION;
		return (-1);
	}
	if (next_value(&str, scene->height) == -1)
		return (-1);
	errno = (*pass_whitespaces(&str) == 0) ? SUCCESS : ERR_EXTRA_CHAR_AFTER;
	return ((*pass_whitespaces(&str) == 0) ? 1 : -1);
}

static int	parse_fc_main(char **str, unsigned int *color)
{
	if (color_component(str, RED, color) == -1)
		return (-1);
	pass_whitespaces(str);
	if (**str == ',')
		(*str)++;
	else
	{
		errno = (*pass_whitespaces(str) == 0) ? ERR_NO_COLOR : ERR_NO_COMMA;
		errno = (**str != ',' && !ft_isdigit(**str)) ? ERR_EXTRA_CHAR : errno;
		return (-1);
	}
	if (color_component(str, GREEN, color) == -1)
		return (-1);
	pass_whitespaces(str);
	if (**str == ',')
		(*str)++;
	else
	{
		errno = (*pass_whitespaces(str) == 0) ? ERR_NO_COLOR : ERR_NO_COMMA;
		errno = (**str != ',' && !ft_isdigit(**str)) ? ERR_EXTRA_CHAR : errno;
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
		errno = ERR_RE_CONFIG;
		return (-1);
	}
	if (parse_fc_main(&str, color) == -1)
		return (-1);
	while (*str == ' ' || *str == '\t')
		str++;
	if (!*str)
		return (1);
	errno = ERR_EXTRA_CHAR_AFTER;
	return (-1);
}

static int	parse_after_texture_path(char *begin, char *after, char **path)
{
	char	*end;

	end = after;
	pass_whitespaces(&after);
	if (!*after)
	{
		*end = '\0';
		if ((is_valid_path(begin)) == -1)
			return (-1);
		*path = ft_strdup(begin);
		return (1);
	}
	errno = ERR_EXTRA_CHAR_AFTER;
	return (-1);
}

int			parse_texture_path(char *str, char **path)
{
	char	*ptr;

	if (*path)
	{
		errno = ERR_RE_CONFIG;
		return (-1);
	}
	pass_whitespaces(&str);
	if (!(ptr = ft_strnstr(str, ".xpm", ft_strlen(str))))
	{
		errno = ERR_EXTEN_TEXTURE;
		return (-1);
	}
	ptr += 4;
	return (parse_after_texture_path(str, ptr, path));
}
