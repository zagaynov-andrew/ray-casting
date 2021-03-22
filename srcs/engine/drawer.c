/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:30:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/22 22:11:05 by ngamora          ###   ########.fr       */
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
