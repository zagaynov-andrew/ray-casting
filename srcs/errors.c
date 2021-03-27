/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/28 12:23:33 by nforce            #+#    #+#             */
/*   Updated: 2021/03/27 09:57:44 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d_errors.h"
#include <errno.h>
#include <stdio.h>

int		print_error_string(char *str)
{
	write(2, str, ft_strlen(str));
	return (EXIT_FAILURE);
}

void	print_error(void)
{
	if (errno == 0)
		return ;
	ft_putstr_fd("Error\n", 2);
	if (errno > 0 && errno < 134)
		perror(NULL);
	errno == ERR_ABS_START_POS ? ft_putstr_fd("Absence of " \
					"starting position of the player\n", 2) : 0;
	errno == ERR_REP_START_POS ? ft_putstr_fd("Repeated " \
					"starting position of the player\n", 2) : 0;
	errno == ERR_EXTRA_CHAR_BETWEEN ? ft_putstr_fd("Extra character(-s) in config file. The configurations should be listed first then the map\n", 2) : 0;
	errno == ERR_NO_MAP ? ft_putstr_fd("No map at the end of file\n", 2) : 0;
	errno == ERR_EMPTY_LINE_MAP ? ft_putstr_fd("Empty line in the map\n", 2) : 0;
	errno == ERR_NO_COMMA ? ft_putstr_fd("No comma between the color components\n", 2) : 0;
	errno == ERR_RE_CONFIG ? ft_putstr_fd("Re-configuration\n", 2) : 0;
	errno == ERR_EXTRA_CHAR_AFTER ? ft_putstr_fd("Extra characters after configuration\n", 2) : 0;
	errno == ERR_RSOLUTION ? ft_putstr_fd("The screen resolution is not greater than zero in the config \"R\"\n", 2) : 0;
	errno == ERR_EXTEN_TEXTURE ? ft_putstr_fd("Invalid texture file extension\n", 2) : 0;
	errno == ERR_TEXTURE_NOT_EXIST ? ft_putstr_fd("Texture file not exist\n", 2) : 0;
	errno == ERR_EXTRA_CHAR ? ft_putstr_fd("Extra character in the configuration\n", 2) : 0;
	errno == ERR_INVALID_COLOR ? ft_putstr_fd("The color component is not included in the range from 0 to 255\n", 2) : 0;
	errno == ERR_COLOR_CONFIG ? ft_putstr_fd("Invalid color format\n", 2) : 0;
	errno == ERR_NO_WALL ? ft_putstr_fd("The map is not surrounded by walls everywhere\n", 2) : 0;
	errno == ERR_NO_COLOR ? ft_putstr_fd("No three components of color\n", 2) : 0;
	errno == ERR_EXTRA_MAP ? ft_putstr_fd("Extra character in the map\n", 2) : 0;
}