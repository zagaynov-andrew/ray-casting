/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 10:30:55 by nforce            #+#    #+#             */
/*   Updated: 2021/03/13 08:38:56 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

// void	draw_line(t_data *data, t_point* p0, t_point* p1, int color)
// {
// 	t_point	delta;
// 	t_point	point;
// 	int	error;
// 	int	delta_err;
// 	int	dir_y;
// 	int dir_x;
// 	int tmp;
	
// 	if (p0->x > p1->x)
// 	{
// 		tmp = p0->x;
// 		p0->x = p1->x;
// 		p1->x = tmp;
// 		tmp = p0->y;
// 		p0->y = p1->y;
// 		p1->y = tmp;
// 	}
// 	delta.x = ft_abs(p1->x - p0->x);
// 	delta.y = ft_abs(p1->y - p0->y);
// 	if (delta.x >= delta.y)
// 	{
// 		error = 0;
// 		delta_err = (delta.y + 1);
// 		dir_y = p1->y - p0->y;
// 		if (dir_y > 0)
// 			dir_y = 1;
// 		if (dir_y < 0)
// 			dir_y = -1;
// 		point.y = p0->y;
// 		point.x = p0->x;
// 		while (point.x < p1->x)
// 		{
// 			pixel_put(data, point.x, point.y, color);
// 			error += delta_err;
// 			if (error >= (delta.x + 1))
// 			{
// 				point.y += dir_y;
// 				error -= delta.x + 1;
// 			}
// 			point.x++;
// 		}
// 	}
// 	else
// 	{
// 		error = 0;
// 		delta_err = (delta.x + 1);
// 		dir_x = p1->x - p0->x;
// 		if (dir_x > 0)
// 			dir_x = 1;
// 		if (dir_x < 0)
// 			dir_x = -1;
// 		point.y = p0->y;
// 		point.x = p0->x;
// 		while (point.y < p1->y)
// 		{
// 			pixel_put(data, point.x, point.y, color);
// 			error += delta_err;
// 			if (error >= (delta.y + 1))
// 			{
// 				point.x += dir_x;
// 				error -= delta.y + 1;
// 			}
// 			point.y++;
// 		}
// 	}
	
// }

static void	draw_line_right(t_data *data, t_point* p0, t_point* p1, int color)
{
	t_point	delta;
	t_point	point;
	int	error;
	int	delta_err;
	int	dir_y;

	delta.x = ft_abs(p1->x - p0->x);
	delta.y = ft_abs(p1->y - p0->y);
	if (delta.x >= delta.y)
	{
		error = 0;
		delta_err = (delta.y + 1);
		dir_y = p1->y - p0->y;
		if (dir_y > 0)
			dir_y = 1;
		if (dir_y < 0)
			dir_y = -1;
		point.y = p0->y;
		point.x = p0->x;
		while (point.x < p1->x)
		{
			pixel_put(data, point.x, point.y, color);
				error += delta_err;
			if (error >= (delta.x + 1))
			{
				point.y += dir_y;
				error -= delta.x + 1;
			}
			point.x++;
		}
	}
}

void	draw_line(t_data *data, t_point* p0, t_point* p1, int color)
{
	t_point	delta;
	t_point	point;
	int	error;
	int	delta_err;
	int	dir_x;
	int tmp;
	
	if (p0->x > p1->x || p0->y < p1->y)
	{
		tmp = p0->x;
		p0->x = p1->x;
		p1->x = tmp;
		tmp = p0->y;
		p0->y = p1->y;
		p1->y = tmp;
	}
	delta.x = ft_abs(p1->x - p0->x);
	delta.y = ft_abs(p1->y - p0->y);
	if (delta.x >= delta.y)
	{
		draw_line_right(data, p0, p1, color);
	}
	else
	{
		error = 0;
		delta_err = (delta.x + 1);
		dir_x = p1->x - p0->x;
		if (dir_x > 0)
			dir_x = 1;
		if (dir_x < 0)
			dir_x = -1;
		point.x = p0->x;
		point.y = p0->y;
		while (point.y > p1->y)
		{
			pixel_put(data, point.x, point.y, color);
			error += delta_err;
			if (error >= (delta.y + 1))
			{
				point.x += dir_x;
				error -= delta.y + 1;
			}
			point.y--;
		}
	}
	
}