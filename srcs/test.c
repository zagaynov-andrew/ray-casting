/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:23:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/20 18:30:15 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <limits.h>
#include "../cub3d.h"

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
// 	t_scene *scene = scene_new();
// 	int res = parse_r("", scene);
// 	printf("width\t= %i\n", scene->width);
// 	printf("height\t= %i\n", scene->height);
// 	printf("res\t= %i\n", res);
// 	printf("errno\t= %i\n", errno);
// 	return (0);
// }

// int main()
// {
// 	t_scene *scene = scene_new();
// 	int res = parse_f("", scene);
// 	printf("color\t= %X\n", scene->f);
// 	printf("color\t= %X\n", 2897730);
// 	printf("res\t= %i\n", res);
// 	printf("errno\t= %i\n", errno);
// 	return (0);
// }

// int main()
// {
// 	unsigned int color = 0x1000000;
// 	int res = get_color(&color, BLUE, 255);
// 	res = get_color(&color, RED, 254);
// 	printf("color\t= %X\n", color);
// 	printf("res\t= %i\n", res);
// 	printf("errno\t= %i\n", errno);
// 	return (0);
// }

// int main()
// {
// 	t_scene *scene = scene_new();
// 	char *line = ft_strdup(" 	./file.xpm 	");
// 	int res = parse_texture_path(line, &(scene->no));
// 	printf("path\t= \"%s\"\n", scene->no);
// 	printf("res\t= %i\n", res);
// 	printf("errno\t= %i\n", errno);
// 	free(scene->no);
// 	free(scene);
// 	free(line);
// 	return (0);
// }

// int main()
// {
// 	t_scene *scene = parse_cub("./configs.cub");
// 	// printf("scene\t= %p\n", scene);
// 	if (!scene)
// 		print_error();
// 	else
// 	{
// 		print_scene(scene);
// 		// printf("\n");
// 		// int i = 0;
// 		// while (i < (int)scene->map->size)
// 		// {
// 		// 	printf("%s\n", (char*)(scene->map->data)[i]);
// 		// 	i++;
// 		// }
// 		// if (is_valid_map(scene->map) == 1)
// 		// 	printf(":D GOOOD :D\n");
// 		// else
// 		// 	printf(":C :C :C\n");
// 		free_scene(scene);
// 	}
// 	return (0);
// }

// int main()
// {
// 	t_scene *scene = parse_cub("./configs.cub");
// 	if (is_valid_map_line("    1 1 1 1 1 1N1 1 1 1 1 1      11 101 101 111 101               101 1     ", scene))
// 		printf(":D GOOOD :D\n");
// 	else
// 		printf(":C :C :C\n");
// 	if (is_valid_map_line("    1 1 1 1 1 1 1 1 1 1 1      11 101 101 111 101               1201 1     ", scene))
// 		printf(":D GOOOD :D\n");
// 	else
// 		printf(":C :C :C\n");
// 	return (0);
// }

// #include "../libs/minilibx-linux/mlx.h"

// void            my_mlx_pixel_put(t_img *img, int x, int y, int color)
// {
//     char    *dst;

//     dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// int             main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_img  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 500, 700, "Hello world!");
//     img.img = mlx_new_image(mlx, 500, 700);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
//                                  &img.endian);
//     pixel_put(&img, 5, 5, 0x00FF0000);
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx);
// }

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

// int             key_hook(int key_code, char *vars)
// {
// 	key_code = key_code;
// 	vars = vars;
//     printf("Hello from key_hook!\n");
// 	return (0);
// }
int	key_hook(int key_code, char *msg)
{
	printf("%s %i\n", msg, key_code);
	return (key_code);
}

int				is_wall(t_game *game, t_vec2 *ray_dir)
{
	char	*line;
	t_vec2	cur;
	t_vec2	begin;
	int		flag;

	cur.x = game->player->pos.x + ray_dir->x;
	cur.y = game->player->pos.y + ray_dir->y;
	flag = 0;
	line = (char*)((game->scene->map->data)[cur.y / CUB_SIZE]);
	if (line[cur.x / CUB_SIZE] == WALL)
		flag = 1;
	if ((cur.x % CUB_SIZE == 0 || cur.y % CUB_SIZE == 0) && flag == 1)
	{
		return (get_side(game, &cur));
	}
	cur.x = game->player->pos.x + ray_dir->x - 1;
	cur.y = game->player->pos.y + ray_dir->y - 1;
	vec2_cpy(&begin, &cur);
	while (cur.y < begin.y + 3)
	{
		cur.x = begin.x;
		while (cur.x < begin.x + 3)
		{
			line = (char*)((game->scene->map->data)[cur.y / CUB_SIZE]);
			if (line[cur.x / CUB_SIZE] == WALL)
				flag = 1;
			if ((cur.x % CUB_SIZE == 0 || cur.y % CUB_SIZE == 0) && flag == 1)
				return (get_side(game, &cur));
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

int				is_wall_around_point(t_game *game, int x, int y)
{
	t_vec	*map;
	char	*line;
	t_vec2	cur;
	t_vec2	begin;

	cur.x = x - EPSILON;
	cur.y = y - EPSILON;
	vec2_cpy(&begin, &cur);
	map = game->scene->map;
	while (cur.y < begin.y + 2 * EPSILON + 1)
	{
		cur.x = begin.x;
		while (cur.x < begin.x + 2 * EPSILON + 1)
		{
			line = (char*)((map->data)[cur.y / CUB_SIZE]);
			if (line[cur.x / CUB_SIZE] == WALL)
				return (1);
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

int			cut_line(t_game *game, t_vec2 *ray_dir)
{
	t_dda	dda;
	t_vec2	dir;
	int		side;

	init_dda(&dda, game, ray_dir);
	vec2_cpy(&dir, ray_dir);
	while (1)
	{
		if (dda.side_dist_x < dda.side_dist_y)
			vec2_change_length(&dir, dda.side_dist_x);
		else
			vec2_change_length(&dir, dda.side_dist_y);
		game->cur_depth = vec2_length(&dir);
		if ((side = is_wall(game, &dir)) != 0)
		{
			vec2_cpy(ray_dir, &dir);
			return (side);
		}
		if (dda.side_dist_x < dda.side_dist_y)
			dda.side_dist_x += dda.delta_dist_x;
		else
			dda.side_dist_y += dda.delta_dist_y;
		vec2_cpy(&dir, ray_dir);
	}
	return (side);
}

void			draw_rays(t_game *game)
{
	int		i;
	t_vec2	const_dir;
	t_vec2	ray_dir;
	float	angle;

	int delta = (int)ceil(((float)game->img->width) / (NUM_RAYS - 1));
	vec2_init(&ray_dir, RAY_LEN, 0);
	angle = game->player->cam_angle - FOV / 2;
	vec2_cpy(&const_dir, &ray_dir);
	rotate(&ray_dir, angle);
	t_vec2 begin;
	t_vec2 end;
	begin.x = game->img->width;
	// begin.x = delta * NUM_RAYS / 2 + game->img->width / 2;
	end.x = begin.x - delta;
	i = 0;
	while (i < NUM_RAYS)
	{
		set_cur_ray_angle(game, angle);
		int side = cut_line(game, &ray_dir);
		side = side + 0;
		int depth = round((float)vec2_length(&ray_dir) * cos(game->player->cam_angle - angle));
		// int depth = vec2_length(&ray_dir);
		game->last_depth = depth;
		int hight = (NUM_RAYS / (2 * tan(FOV / 2)) * CUB_SIZE / depth);
		begin.y = game->img->height / 2 - hight / 2;
		end.y = game->img->height / 2 + hight / 2;
		int c;
		if (side == NO)
			c = 0x00FF0000;
		else if (side == SO)
			c = 0x0000FFFF;
		else if (side == WE)
			c = 0x00FFFF00;
		else if (side == EA)
			c = 0x004B0082;
		else
			c = 0x00FFFFFF;
		// t_vec2 p;
		// p.x = ray_dir.x + game->player->pos.x;
		// p.y = ray_dir.y + game->player->pos.y;
		// if (is_corner(game, &p))
		// 	c = 0x00000000;
		// int c = 255 / (1 + depth * depth * 0.000002);
		c += 0;
		// draw_rectangle(game->img, &end, &begin, c << 16 | c / 2 << 8 | c / 3);
		draw_rectangle(game->img, &end, &begin, c);
		// draw_line(game->img, &game->player->pos, &ray_dir, c);
		end.x -= delta;
		begin.x -= delta;
		angle += FOV / (NUM_RAYS - 1);
		vec2_cpy(&ray_dir, &const_dir);
		rotate(&ray_dir, angle);
		i++;
	}
	game->last_side = NOTHING;
}

void			init_game(t_game *game, t_scene **scene, t_player *player, t_img *img)
{
	printf("%p\n", (*scene)->map);
	game->scene = *scene;
	game->player = player;
	game->img = img;
}

void			init_mlx(t_game *game, void **mlx, void **mlx_win)
{
	game->mlx = *mlx;
	game->win = *mlx_win;
}

void			set_cur_ray_angle(t_game *game, float cur_ray_angle)
{
	game->cur_ray_angle = cur_ray_angle;
	if (game->cur_ray_angle >= 2 * M_PI)
		game->cur_ray_angle -= 2 * M_PI;
	if (game->cur_ray_angle < 0)
		game->cur_ray_angle += 2 * M_PI;
}

int				main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_img		img;
	t_player	player;
	t_game		game;

	t_scene *scene = parse_cub("./configs.cub");
	if (!scene)
	{
		print_error();
		free_scene(scene);
		exit(0);
	}

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, scene->width, scene->height, "cub3D");
	img.img = mlx_new_image(mlx, scene->width, scene->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
							&img.endian);
	img.width = scene->width;
	img.height = scene->height;
	init_mlx(&game, &mlx, &mlx_win);

	// print_scene(scene);

	printf("%p\n", scene->map);
	init_game(&game, &scene, &player, &img);
	game.player->movement = STOP;
	game.last_side = VERTICAL;
	game.last_depth = 0;

	// draw_map(&img, scene->map);
	// draw_grid(&img, 0x00FFFFFF);

	init_player(&player, scene);
	// game.player->cam_angle = 1.22;

	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_loop_hook(game.mlx, &render_frame, &game);

	// mlx_key_hook(mlx_win, key_hook, "message");
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// free_scene(scene);
	mlx_loop(mlx);
}
