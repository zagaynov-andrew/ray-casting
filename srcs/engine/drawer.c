/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:30:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 18:11:37 by ngamora          ###   ########.fr       */
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

void	draw_grid(t_img *img, int color)
{
	t_vec2	begin;
	t_vec2	vec;

	begin.x = 0;
	begin.y = 0;
	vec.x = 0;
	vec.y = img->height;
	while (begin.x < img->width)
	{
		draw_line(img, &begin, &vec, color);
		begin.x += CUB_SIZE;
	}
	begin.x = 0;
	begin.y = 0;
	vec.x = img->width;
	vec.y = 0;
	while (begin.y < img->height)
	{
		draw_line(img, &begin, &vec, color);
		begin.y += CUB_SIZE;
	}
}

void	img_clear(t_img *img)
{
	int	x;
	int y;
	
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

void	draw_line(t_img *img, t_vec2* begin, t_vec2* vec, int color)
{
	t_vec2	delta;
	t_vec2	point;
	t_vec2	p1;
	t_vec2	p0;
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
			pixel_put(img, point.x, point.y, color);
			error += delta_err;
			if (error >= (delta.x + 1))
			{
				point.y += dir_y;
				error -= delta.x + 1;
			}
			point.x += dir_x;
		}
		pixel_put(img, point.x, point.y, color);
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
			pixel_put(img, point.x, point.y, color);
			error += delta_err;
			if (error >= (delta.y + 1))
			{
				point.x += dir_x;
				error -= delta.y + 1;
			}
			point.y += dir_y;
		}
		pixel_put(img, point.x, point.y, color);
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

void	draw_square(t_img *img, t_vec2 *p0, int size, int color)
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
			pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
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

void	draw_square_centre(t_img *img, t_vec2 *p0, int size, int color)
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
			pixel_put(img, x, y, color);
			y++;
		}
		x++;
	}
}
