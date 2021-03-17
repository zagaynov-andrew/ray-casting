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

// void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
// {
//     char    *dst;

//     dst = data->addr + (y * data->size_line + x * (data->bits_per_pixel / 8));
//     *(unsigned int*)dst = color;
// }

// int             main(void)
// {
//     void    *mlx;
//     void    *mlx_win;
//     t_data  img;

//     mlx = mlx_init();
//     mlx_win = mlx_new_window(mlx, 500, 700, "Hello world!");
//     img.img = mlx_new_image(mlx, 500, 700);
//     img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
//                                  &img.endian);
//     pixel_put(&img, 5, 5, 0x00FF0000);
//     mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
//     mlx_loop(mlx);
// }

void	draw_map(t_data *data, t_vec *map)
{
	int		i;
	int		j;
	int		line_len;
	char	*line;
	t_point	p;

	i = 0;
	while (i < (int)map->size)
	{
		line = (char*)((map->data)[i]);
		line_len = ft_strlen(line);
		j = 0;
		while (j < line_len)
		{
			printf("%c", line[j]);
			if (line[j] == WALL)
			{
				p.x = j * CUB_SIZE;
				p.y = i * CUB_SIZE;
				draw_square(data, &p, CUB_SIZE, 0x00FF0000);
			}
			j++;
		}
		printf("\n");
		i++;
	}
	data = 0;
}


int	key_hook(int key_code, char *msg)
{
	printf("%s %i", msg, key_code);
	return (key_code);
}

void				set_start_position(t_player *player, t_vec *map)
{
	int		x;
	int		y;
	char	*line;

	y = 0;
	while (y < (int)map->size)
	{
		line = (char*)((map->data)[y]);
		x = 0;
		while (line[x])
		{
			if (ft_char_in_set("NSEW", line[x]))
			{
				player->pos.x = x * CUB_SIZE + CUB_SIZE / 2;
				player->pos.y = y * CUB_SIZE + CUB_SIZE / 2;
				return ;
			}
			x++;
		}
		y++;
	}
}

void	init_player(t_player *player, t_scene *scene)
{
	set_start_position(player, scene->map);
	if (scene->start_pos_flag == 'N')
		player->cam_angle = M_PI_2;
	else if (scene->start_pos_flag == 'S')
		player->cam_angle = 3 * M_PI_2;
	else if (scene->start_pos_flag == 'E')
		player->cam_angle = 0;
	else if (scene->start_pos_flag == 'W')
		player->cam_angle = M_PI;

}

void			vec2_cpy(t_vec2 *dst, const t_vec2 *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

void			cut_line(t_data *data, t_player *player, t_vec2 *ray_dir)
{
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	t_vec2	dir;

	vec2_cpy(&dir, ray_dir);
	delta_dist_x = get_delta_dist_x(&dir);
	side_dist_x = get_side_dist_x(player, &dir, delta_dist_x);
	vec2_change_length(&dir, side_dist_x);
	//-----
	t_point p;
	p.x = player->pos.x + dir.x;
	p.y = player->pos.y + dir.y;
	// draw_square_centre(data, &p, 2, 0x00FF0000);
	pixel_put(data, p.x, p.y, 0x00FF0000);
	//-----
	// pixel_put(data, dir.x, dir.y, 0x00FFFFFF);
	vec2_cpy(&dir, ray_dir);

	delta_dist_y = get_delta_dist_y(&dir);
	side_dist_y = get_side_dist_y(player, &dir, side_dist_x);
	p.x = player->pos.x + dir.x;
	p.y = player->pos.y + dir.y;
	vec2_change_length(&dir, delta_dist_x);
	pixel_put(data, p.x, p.y, 0x00FF0000);
	//Check if ray has hit a wall

	// while (1)
	// {
	// 	if (side_dist_x < side_dist_y)
	// 	{
	// 		side_dist_x += delta_dist_x;
	// 	}
	// 	else
	// 	{
	// 		side_dist_y += delta_dist_y;
	// 	}
	// 	//Check if ray has hit a wall
	// }
}

void			draw_rays(t_data *data, t_player *player, int color)
{
	int		i;
	t_vec2	ray_dir;
	float	angle;

	i = 0;
	ray_dir.x = RAY_LEN;
	ray_dir.y = 0;
	angle = player->cam_angle - FOV / 2;
	rotate(&ray_dir, angle);
	while (i < NUM_RAYS)
	{
		// cut_line(data, player, &ray_dir);
		draw_line(data, &player->pos, &ray_dir, color);
		cut_line(data, player, &ray_dir);
		rotate(&ray_dir, FOV / NUM_RAYS);
		i++;
	}
}

float			get_side_dist_x(t_player *player, t_vec2 *ray_dir, float delta_dist_x)
{
	int		num_line;
	int		line_x;
	float	similarity_coeff;

	num_line = player->pos.x / CUB_SIZE;
	if (ray_dir->x < 0)
		num_line++;
	line_x = num_line * CUB_SIZE;
	similarity_coeff = (float)ft_abs(player->pos.x - line_x) / CUB_SIZE;
	return ((1. - similarity_coeff) * delta_dist_x);
}

float			get_side_dist_y(t_player *player, t_vec2 *ray_dir, float delta_dist_y)
{
	int		num_line;
	int		line_y;
	float	similarity_coeff;

	num_line = player->pos.y / CUB_SIZE;
	if (ray_dir->y < 0)
		num_line++;
	line_y = num_line * CUB_SIZE;
	similarity_coeff = (float)ft_abs(player->pos.y - line_y) / CUB_SIZE;
	return ((1. - similarity_coeff) * delta_dist_y);
}

float			get_delta_dist_x(t_vec2 *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + ((float)(ray_dir->y * ray_dir->y)) / (ray_dir->x * ray_dir->x)));
}

float			get_delta_dist_y(t_vec2 *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + ((float)(ray_dir->x * ray_dir->x)) / (ray_dir->y * ray_dir->y)));
}

float			lenght(t_vec2f *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y));
}

void			normalize(t_vec2f *vec)
{
	float len;

	len = lenght(vec);
	vec->x = vec->x / len;
	vec->y = vec->y / len;
}

void			multiply(t_vec2f *vec, float num)
{
	vec->x *= num;
	vec->y *= num;
}

void			vec2_change_length(t_vec2 *vec, float length)
{
	t_vec2f	vec2f;

	vec2f.x = (float)vec->x;
	vec2f.y = (float)vec->y;
	normalize(&vec2f);
	multiply(&vec2f, length);
	vec->x = (int)round(vec2f.x);
	vec->y = (int)round(vec2f.y);
}

// void			to_vec2(t_vec2 *vec2, t_vec2f *vec2f, float length)
// {
// 	vec2->x = (int)round(vec2f->x);
// 	vec2->y = (int)round(vec2f->y);
// }

int				main(void)
{
	void		*mlx;
	void		*mlx_win;
	t_data		img;
	t_player	player;

	t_scene *scene = parse_cub("./configs.cub");

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, scene->width, scene->height, "Hello world!");
	img.img = mlx_new_image(mlx, scene->width, scene->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
							&img.endian);
	img.width = scene->width;
	img.height = scene->height;
	if (!scene)
	{
		print_error();
		exit(0);
	}
	else
	{
		print_scene(scene);
		draw_map(&img, scene->map);
		draw_grid(&img, 0x00FFFFFF);
	}
	init_player(&player, scene);
	// player.pos.y += 1;
	free_scene(scene);
	printf("\npos = [%d, %d]\n", player.pos.x, player.pos.y);
	draw_square_centre(&img, &player.pos, CUB_SIZE, 0x0000FF00);


	draw_rays(&img, &player, 0x0000FFFF);
	t_vec2 dir;
	dir.x = 1;
	dir.y = 2;
	// float side_dist_x = get_side_dist_x(&player, &dir, get_delta_dist_x(&dir));
	// printf("delta_dist_x\t= %f\n", get_delta_dist_x(&dir));
	// printf("side_dist_x\t= %f\n", get_side_dist_x(&player, &dir, get_delta_dist_x(&dir)));

	// t_vec2f dirf;
	// dirf.x = dir.x;
	// dirf.y = dir.y;
	// change_length(&dirf, side_dist_x);
	// printf("[%f, %f]\n", dirf.x, dirf.y);

	// mlx_key_hook(mlx_win, key_hook, "message");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
