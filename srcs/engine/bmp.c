/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/24 14:35:13 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/27 12:39:34 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	write_header(t_game *game, int fd)
{
	int value;

	write(fd, "BM", 2);
	value = 54 + game->scene->width * game->scene->height * 4;
	write(fd, &value, 4);
	value = 0;
	write(fd, &value, 2);
	write(fd, &value, 2);
	value = 54;
	write(fd, &value, 4);
	value = 40;
	write(fd, &value, 4);
	write(fd, &game->scene->width, 4);
	write(fd, &game->scene->height, 4);
	value = 1;
	write(fd, &value, 2);
	write(fd, &game->img.bits_per_pixel, 2);
	value = 0;
	write(fd, &value, 4);
	write(fd, &value, 4);
	write(fd, &value, 4);
	write(fd, &value, 4);
	write(fd, &value, 4);
	write(fd, &value, 4);
}

void	save_bmp_util(t_game *game)
{
	int	fd;
	int	y;

	if ((fd = open("./screenshot.bmp", O_TRUNC | O_CREAT | O_RDWR)) == -1)
	{
		write(2, "Errno\nImpossible to create screenshot.bmp\n", 42);
		return ;
	}
	write_header(game, fd);
	y = game->scene->height - 1;
	while (y >= 0)
	{
		write(fd, game->img.addr + y * game->img.width * 4,
											4 * game->scene->width);
		y--;
	}
	system("chmod 777 screenshot.bmp");
}

void	save_bmp(t_game *game)
{
	draw_floor(game);
	draw_ceiling(game);
	draw_walls(game);
	draw_sprites(game);
	save_bmp_util(game);
	exit_game(game);
}
