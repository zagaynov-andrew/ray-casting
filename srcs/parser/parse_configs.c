/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_configs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 21:08:36 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:06:16 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			parse_r_width(char **str, t_scene *scene)
{
	int	overflow;

	if (scene->width > 0 || scene->height > 0)
	{
		errno = ERR_RE_CONFIG;
		return (-1);
	}
	if ((overflow = check_int_overflow(*str)) == -1)
		return (-1);
	if ((scene->width = ft_atoi(*str)) <= 0 && overflow != 1)
	{
		errno = ERR_RESOLUTION;
		return (-1);
	}
	if (overflow == 1)
		scene->width = 2147483647;
	if (overflow == 2)
		scene->width = -2147483648;
	if (next_value(str) == -1)
		return (-1);
	return (0);
}

int			parse_r_height(char **str, t_scene *scene)
{
	int	overflow;

	if (!ft_isdigit(*pass_whitespaces(str)) && **str != '-')
	{
		errno = ERR_EXTRA_CHAR;
		return (-1);
	}
	if ((overflow = check_int_overflow(*str)) == -1)
		return (-1);
	if ((scene->height = ft_atoi(*str)) <= 0 && overflow != 1)
	{
		errno = ERR_RESOLUTION;
		return (-1);
	}
	if (overflow == 1)
		scene->height = 2147483647;
	if (overflow == 2)
		scene->width = -2147483648;
	if (next_value(str) == -1)
		return (-1);
	return (0);
}

int			parse_r(char *str, t_scene *scene)
{
	void	*mlx;
	int		screen_w;
	int		screen_h;

	if (parse_r_width(&str, scene) == -1)
		return (-1);
	if (parse_r_height(&str, scene) == -1)
		return (-1);
	mlx = mlx_init();
	if (!mlx)
	{
		errno = ENOMEM;
		return (-1);
	}
	mlx_get_screen_size(mlx, &screen_w, &screen_h);
	if (scene->width > screen_w)
		scene->width = screen_w;
	if (scene->height > screen_h)
		scene->height = screen_h;
	mlx_destroy_display(mlx);
	free(mlx);
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
