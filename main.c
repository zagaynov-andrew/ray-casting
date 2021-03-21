/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:36:22 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/21 12:36:23 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <mlx.h>

# define CUB_SIZE 64

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				size_line;
	int				width;
	int				height;
	int				endian;
}					t_img;

typedef struct		s_game
{
	void			*mlx;
	void			*win;
	t_img			*img;
	int				last_side;
	int				last_depth;
	int				cur_depth;
	float			cur_ray_angle;
}					t_game;

typedef struct		s_vec2
{
	int				x;
	int				y;
}					t_vec2;

typedef struct		s_vec2f
{
	float			x;
	float			y;
}					t_vec2f;

unsigned int	get_pixel_color(t_img *img, int x, int y)
{
	char *dst;

	if (x < 0 || y < 0)
		return (0);
	if (x >= img->width || y >= img->height)
		return (0);
	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	return (*(unsigned int*)dst);
}

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

void			draw_texture_line(t_game *game, t_vec2 win_point, t_vec2 info)
{
	t_vec2f	tex_pos;
	int		height;
	float	step;
	int		i;
	t_img	tex;

	tex_pos.x = (float)info.x;
	tex_pos.y = 0;
	height = info.y;
	printf("%i\n",  game->img->height);
	win_point.y -= height / 2;
	step = (float)CUB_SIZE / height;

	tex.img = mlx_xpm_file_to_image(game->mlx, "./WALL33.xpm", &tex.width, &tex.height);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.size_line,
							&tex.endian);

	i = 0;
	while (i < height)
	{
		pixel_put(game->img, win_point.x, win_point.y + i,
						get_pixel_color(&tex, (int)tex_pos.x, (int)tex_pos.y));
		tex_pos.y += step;
		i++;
	}
}

int				main(void)
{
	t_img img;

	void *mlx = mlx_init();
	void *mlx_win = mlx_new_window(mlx, 200, 200, "test");

	t_game game;
	game.mlx = mlx;
	game.win = mlx_win;
	game.img = &img;
	img.width = 200;
	img.height = 200;
	img.img = mlx_new_image(mlx, img.width, img.height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
							&img.endian);

	t_img tex;

	tex.img = mlx_xpm_file_to_image(mlx, "./WALL33.xpm", &tex.width, &tex.height);
	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.size_line,
							&tex.endian);
	// printf("%i\t%i\n", tex.width, tex.height);

	// printf("%u\n",  get_pixel_color(&tex, 63, 63));

	t_vec2	win_point;
	t_vec2	info;
	win_point.x = 5; // сдвиг на экране по x
	win_point.y = 100; //центр экрана по y
	info.x = 0; // сдвиг в текстуре
	info.y = 200; // реальная высота

	int i = 0;
	while (i < 64)
	{
		draw_texture_line(&game, win_point, info);
		// win_point.y = 100;
		// info.y = 100;
		win_point.x++;
		info.x++;
		i++;
	}


	mlx_put_image_to_window(game.mlx, game.win, game.img->img, 0, 0);
	// mlx_put_image_to_window(game.mlx, game.win, tex.img, 0, 0);
	mlx_loop(mlx);
}
