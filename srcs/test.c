/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:23:55 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/24 12:19:43 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <limits.h>
#include "../cub3d.h"

// int			is_sprite(t_game *game, int x, int y)
// {
// 	t_vec	*map;
// 	char	*line;

// 	map = game->scene->map;
// 	line = (char*)((map->data)[y / CUB_SIZE]);
// 	if (line[x / CUB_SIZE] == SPRITE)
// 		return (1);
// 	return (0);
// }

// void		check_sprite(t_game *game, t_dda *dda, const t_vec2f *dir)
// {
// 	float	dir_len;
// 	t_vec2f check_dir;
// 	// t_vec2f check_dir;

// 	dir_len = vec2f_length(dir);
// 	if (ft_abs(dir->x) >= ft_abs(dir->y))
// 		dir_len -= dda->delta_dist_x / 2;
// 	else
// 		dir_len -= dda->delta_dist_y / 2;
// 	if (dir_len <= 0)
// 		return ;
// 	vec2f_cpy(&check_dir, dir);
// 	vec2f_change_length(&check_dir, dir_len);
// 	if (is_sprite(game,
// 		game->player->pos.x + (int)round(check_dir.x),
// 		game->player->pos.y + (int)round(check_dir.y)) == 1)
// 		printf("1\n");
// 	else
// 		printf("0\n");
// }

int			cut_line(t_game *game, t_vec2f *ray_dir)
{
	t_dda	dda;
	t_vec2f	dir;
	int		side;
	t_vec2	vec2_dir;

	init_dda(&dda, game, ray_dir);
	vec2f_cpy(&dir, ray_dir);
	while (1)
	{
		if (dda.side_dist_x < dda.side_dist_y)
			vec2f_change_length(&dir, dda.side_dist_x);
		else
			vec2f_change_length(&dir, dda.side_dist_y);
		if ((side = is_wall(game, vec2f_to_vec2(&vec2_dir, &dir))) != 0)
		{
			vec2f_cpy(ray_dir, &dir);
			return (side);
		}	
		if (dda.side_dist_x < dda.side_dist_y)
			dda.side_dist_x += dda.delta_dist_x;
		else
			dda.side_dist_y += dda.delta_dist_y;
		vec2f_cpy(&dir, ray_dir);
	}
	return (side);
}

void			draw_rays(t_game *game)
{
	int		i;//
	t_vec2f	const_dir;//
	t_vec2f	ray_dir;//
	float	angle;//

	vec2f_init(&ray_dir, RAY_LEN, 0);
	angle = game->player->cam_angle + FOV / 2;
	vec2f_cpy(&const_dir, &ray_dir);
	vec2f_rotate(&ray_dir, angle);
	t_vec2 begin;
	t_vec2 end;
	begin.x = 0;
	end.x = 0;
	i = 0;

	t_vec2	win_point;
	t_vec2	info;
	win_point.y = game->img->height / 2; //центр экрана по y
	while (i < game->scene->width + 1)
	{
		if (i == 387)
		{
			i+=1;
			i--;
		}
		set_cur_ray_angle(game, angle);
		int side = cut_line(game, &ray_dir);
		int depth = round((float)vec2f_length(&ray_dir) * cos(game->player->cam_angle - angle)); //wal_depth
		game->wall_depth[i] = depth;
		game->angle[i] = angle;
		int hight = ((game->scene->width + 1) / (2 * tan(FOV / 2)) * CUB_SIZE / depth);




		win_point.x = begin.x; // сдвиг на экране по x
		
		if (side == NO || side == SO)
			info.x = (game->player->pos.x + (int)round(ray_dir.x)) % CUB_SIZE; // сдвиг в текстуре
		else
			info.x = (game->player->pos.y + (int)round(ray_dir.y)) % CUB_SIZE; // сдвиг в текстуре
		info.y = hight; // реальная высота
		if (side != NOTHING)
			draw_texture_line(game, win_point, info, side);


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


		// int c = 255 / (1 + depth * depth * 0.000002);
		// draw_rectangle(game->img, &end, &begin, c << 16 | c / 2 << 8 | c / 3);
		// draw_line(game->img, &begin, &end, c);
		c += 0;
		// draw_vertical_line(game->img, &end, &begin, c);

		// draw_rectangle(game->img, &end, &begin, c);
		// t_vec2 end_dir;
		// draw_line(game->img, &game->player->pos, vec2f_to_vec2(&end_dir, &ray_dir), c);
		end.x++;
		begin.x++;
		angle -= FOV / game->scene->width;
		vec2f_cpy(&ray_dir, &const_dir);
		vec2f_rotate(&ray_dir, angle);
		i++;
	}
	game->last_side = NOTHING;
}

// void			iter(void *data)
// {
// 	printf("%i\t%i\n", ((t_sprite*)data)->pos.x, ((t_sprite*)data)->pos.y);
// }



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
	// printf("%p\n", scene->map);
	init_game(&game, &scene, &player, &img);
	game.player->movement = STOP;
	game.last_side = VERTICAL;
	game.wall_depth = (float*)malloc((game.img->width + 1) * sizeof(float)); //!!!!!!!!!!!malloc
	game.angle = (float*)malloc((game.img->width + 1) * sizeof(float)); //!!!!!!!!!!!malloc
	init_sprites(&game);
	// ft_lstiter(game.sprites, iter);//
	
	
	

	// draw_map(&img, scene->map);
	// draw_grid(&img, 0x00FFFFFF);

	init_player(&player, scene);
	
	
	// vec2_init(&player.pos, 1613, 608);
	// player.cam_angle = 5.93;

	mlx_hook(game.win, 2, 1L << 0, key_pressed, &game);
	mlx_hook(game.win, 3, 1L << 1, key_released, &game);
	mlx_hook(game.win, 33, 1L << 17, exit_game, &game);
	// mlx_hook(game.win, 17, 1L << 17, exit_game, &game);
	mlx_loop_hook(game.mlx, render_frame, &game);
	

	// t_img	no;
	init_textures(&game);
	// no.img = mlx_xpm_file_to_image(game.mlx, "./WALL33.xpm", &no.width, &no.height);
	// no.addr = mlx_get_data_addr(no.img, &no.bits_per_pixel, &no.size_line,
	// 						&no.endian);
	// game.no = &no;


	// mlx_key_hook(mlx_win, key_hook, "message");
	// mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	// free_scene(scene);
	mlx_loop(mlx);
}
