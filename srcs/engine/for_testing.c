/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   for_testing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:15:36 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/24 15:15:59 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

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

void	draw_vertical_line(t_img *img, t_vec2 *begin, t_vec2 *end, int color)
{
	int	y;

	y = end->y;
	while (y <= begin->y)
	{
		pixel_put(img, end->x, y, color);
		y++;
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

void	draw_map(t_img *img, t_vec *map)
{
	int		i;
	int		j;
	int		line_len;
	char	*line;
	t_vec2	p;

	i = 0;
	while (i < (int)map->size)
	{
		line = (char*)((map->data)[i]);
		line_len = ft_strlen(line);
		j = 0;
		while (j < line_len)
		{
			if (line[j] == WALL)
			{
				p.x = j * CUB_SIZE;
				p.y = i * CUB_SIZE;
				draw_square(img, &p, CUB_SIZE, 0x00FF0000);
			}
			j++;
		}
		i++;
	}
}

void	print_scene(t_scene *scene)
{
	printf("==========================\n");
	printf("||R %i %i\t\t||\n", scene->width, scene->height);
	printf("||NO \"%s\"\t||\n", scene->no);
	printf("||SO \"%s\"\t||\n", scene->so);
	printf("||WE \"%s\"\t||\n", scene->we);
	printf("||EA \"%s\"\t||\n", scene->ea);
	printf("||S \"%s\"\t||\n", scene->s);
	printf("||F %X\t\t||\n", scene->f);
	printf("||C %X\t\t||\n", scene->c);
	printf("==========================\n");
}

// int main()
// {
// 	t_scene *scene = parse_cub("./configs.cub");
// 	// printf("scene\t= %p\n", scene);
// 	if (!scene)
// 		print_error();
// 	else
// 	{
// 		print_scene(scene);
// 		free_scene(scene);
// 	}
// 	return (0);
// }
