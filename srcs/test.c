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
	t_point	p;

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

int				is_wall(t_game *game, t_vec2 *ray_dir)
{
	t_vec	*map;
	char	*line;
	t_vec2	cur;
	t_vec2	begin;

	cur.x = game->player->pos.x + ray_dir->x - 1;
	cur.y = game->player->pos.y + ray_dir->y - 1;
	vec2_cpy(&begin, &cur);
	map = game->scene->map;
	while (cur.y < begin.y + 3)
	{
		cur.x = begin.x;
		while (cur.x < begin.x + 3)
		{
			line = (char*)((map->data)[cur.y / CUB_SIZE]);
			char c = line[cur.x / CUB_SIZE];
			c = c;
			if (line[cur.x / CUB_SIZE] == WALL)
				return (1);
			cur.x++;
		}
		cur.y++;
	}
	return (0);
}

void			cut_line(t_game *game, t_vec2 *ray_dir)
{
	float	delta_dist_x;
	float	delta_dist_y;
	float	side_dist_x;
	float	side_dist_y;
	t_vec2	dir;

	delta_dist_x = get_delta_dist_x(ray_dir);
	side_dist_x = get_side_dist_x(game->player, ray_dir, delta_dist_x);
	delta_dist_y = get_delta_dist_y(ray_dir);
	side_dist_y = get_side_dist_y(game->player, ray_dir, delta_dist_y);

	vec2_cpy(&dir, ray_dir);
	while (1)
	{
		if (side_dist_x < side_dist_y)
		{
			vec2_change_length(&dir, side_dist_x);
			if (is_wall(game, &dir) == 1)
			{
				vec2_cpy(ray_dir, &dir);
				return ;
			}
			side_dist_x += delta_dist_x;
		}
		else
		{
			vec2_change_length(&dir, side_dist_y);
			if (is_wall(game, &dir) == 1)
			{
				vec2_cpy(ray_dir, &dir);
				return ;
			}
			side_dist_y += delta_dist_y;
		}
		vec2_cpy(&dir, ray_dir);
	}
}

void			draw_rays(t_game *game, int color)
{
	int		i;
	t_vec2	ray_dir;
	t_vec2	dir;
	float	angle;

	i = 0;
	ray_dir.x = RAY_LEN;
	ray_dir.y = 0;
	angle = game->player->cam_angle - FOV / 2;
	rotate(&ray_dir, angle);
	vec2_cpy(&dir, &ray_dir);
	while (i < NUM_RAYS)
	{
		cut_line(game, &ray_dir);
		draw_line(game->img, &game->player->pos, &ray_dir, color);
		vec2_cpy(&ray_dir, &dir);
		rotate(&ray_dir, FOV / (NUM_RAYS - 1));
		vec2_cpy(&dir, &ray_dir);
		i++;
	}
}

float			get_side_dist_x(const t_player *player, const t_vec2 *ray_dir, float delta_dist_x)
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

float			get_side_dist_y(const t_player *player, const t_vec2 *ray_dir, float delta_dist_y)
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

float			get_delta_dist_x(const t_vec2 *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + ((float)(ray_dir->y * ray_dir->y)) / (ray_dir->x * ray_dir->x)));
}

float			get_delta_dist_y(const t_vec2 *ray_dir)
{
	return (CUB_SIZE * sqrtf(1 + ((float)(ray_dir->x * ray_dir->x)) / (ray_dir->y * ray_dir->y)));
}

float			lenght(const t_vec2f *vec)
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

void			init_game(t_game *game, t_scene *scene, t_player *player, t_img *img)
{
	game->scene = scene;
	game->player = player;
	game->img = img;
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

	print_scene(scene);
	draw_map(&img, scene->map);
	draw_grid(&img, 0x00FFFFFF);

	init_player(&player, scene);

	init_game(&game, scene, &player, &img);

	draw_square_centre(&img, &player.pos, CUB_SIZE, 0x0000FF00);
	draw_rays(&game, 0x0000FFFF);


	// mlx_key_hook(mlx_win, key_hook, "message");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	free_scene(scene);
	mlx_loop(mlx);
}
