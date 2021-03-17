/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:30:55 by nforce            #+#    #+#             */
/*   Updated: 2021/03/17 12:25:26 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"
#include <math.h>

void	pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (x >= data->width || y >= data->height)
		return ;
	if (x < 0 || y < 0)
		return ;
	dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_line(t_data *data, t_point* begin, t_vec2* vec, int color)
{
	t_point	delta;
	t_point	point;
	t_point	p1;
	t_point	p0;
	int	error;
	int	delta_err;
	int	dir_y;
	int dir_x;
	int tmp;

	p0.x = begin->x;
	p0.y = begin->y;
	p1.x = p0.x + vec->x;
	p1.y = p0.y + vec->y;
	delta.x = ft_abs(p1.x - p0.x);
	delta.y = ft_abs(p1.y - p0.y);
	if (delta.x >= delta.y)
	{
		if (p0.x > p1.x || p0.y < p1.y)
		{
			tmp = p0.x;
			p0.x = p1.x;
			p1.x = tmp;
			tmp = p0.y;
			p0.y = p1.y;
			p1.y = tmp;
		}
		error = 0;
		delta_err = (delta.y + 1);
		dir_x = p1.x - p0.x;
		dir_y = p1.y - p0.y;
		if (dir_x > 0)
			dir_x = 1;
		if (dir_x < 0)
			dir_x = -1;
		if (dir_y > 0)
			dir_y = 1;
		if (dir_y < 0)
			dir_y = -1;
		point.y = p0.y;
		point.x = p0.x;
		while (point.x != p1.x)
		{
			pixel_put(data, point.x, point.y, color);
			error += delta_err;
			if (error >= (delta.x + 1))
			{
				point.y += dir_y;
				error -= delta.x + 1;
			}
			point.x += dir_x;
		}
		pixel_put(data, point.x, point.y, color);
	}
	else
	{
		error = 0;
		delta_err = (delta.x + 1);
		dir_x = p1.x - p0.x;
		dir_y = p1.y - p0.y;
		point.y = p0.y;
		point.x = p0.x;
		if (dir_x > 0)
			dir_x = 1;
		if (dir_x < 0)
			dir_x = -1;
		if (dir_y > 0)
			dir_y = 1;
		if (dir_y < 0)
			dir_y = -1;
		while (point.y != p1.y)
		{
			pixel_put(data, point.x, point.y, color);
			error += delta_err;
			if (error >= (delta.y + 1))
			{
				point.x += dir_x;
				error -= delta.y + 1;
			}
			point.y += dir_y;
		}
		pixel_put(data, point.x, point.y, color);
	}

}

void	rotate(t_vec2 *vec, float angle)
{
	t_vec2	tmp;

	tmp.x = (int)round(vec->x * cos(angle) + vec->y * sin(angle));
	tmp.y = (int)round(- vec->x * sin(angle) + vec->y * cos(angle));
	vec->x = tmp.x;
	vec->y = tmp.y;
}

void	draw_square(t_data *data, t_point *p0, int size, int color)
{
	int	x;
	int	y;

	if (size <= 0)
		return ;
	x = p0->x;
	while (x < size + p0->x)
	{
		y = p0->y;
		while (y < size + p0->y)
		{
			pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}

void	draw_square_centre(t_data *data, t_point *p0, int size, int color)
{
	int	x;
	int	y;

	if (size <= 0)
		return ;
	x = p0->x - size / 2;
	while (x < size / 2 + p0->x)
	{
		y = p0->y - size / 2;
		while (y < size / 2 + p0->y)
		{
			pixel_put(data, x, y, color);
			y++;
		}
		x++;
	}
}
