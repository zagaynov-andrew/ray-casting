/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:30:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/26 19:33:06 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x >= img->width || y >= img->height)
		return ;
	if (x < 0 || y < 0)
		return ;
	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	img_clear(t_img *img)
{
	int	x;
	int	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_put(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	draw_floor(t_game *game)
{
	t_vec2 begin;
	t_vec2 end;

	vec2_init(&begin, 0, game->img.height / 2);
	vec2_init(&end, game->img.width, game->img.height + 1);
	draw_rectangle(&game->img, &begin, &end, game->scene->f);
}

void	draw_ceiling(t_game *game)
{
	t_vec2 begin;
	t_vec2 end;

	vec2_init(&begin, 0, 0);
	vec2_init(&end, game->img.width, game->img.height / 2);
	draw_rectangle(&game->img, &begin, &end, game->scene->c);
}

void	draw_rectangle(t_img *img, t_vec2 *begin, t_vec2 *end, int color)
{
	int	x;
	int	x_begin;
	int	y;
	int	y_begin;

	x = (begin->x <= end->x ? begin->x : end->x);
	x_begin = x;
	while (x < x_begin + ft_abs(begin->x - end->x))
	{
		y = (begin->y <= end->y ? begin->y : end->y);
		y_begin = y;
		while (y < y_begin + ft_abs(begin->y - end->y))
		{
			pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}
