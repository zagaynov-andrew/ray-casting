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
				draw_square(data, &p, CUB_SIZE, 0x0000FF00);
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

int             main(void)
{
    void    *mlx;
    void    *mlx_win;
    t_data  img;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "Hello world!");
    img.img = mlx_new_image(mlx, 1920, 1080);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.size_line,
                                 &img.endian);

	t_scene *scene = parse_cub("./configs.cub");
	if (!scene)
		print_error();
	else
	{
		print_scene(scene);
		draw_map(&img, scene->map);
		free_scene(scene);
	}

	// draw_line(&img, &begin, &vec, 0x00FF0000);
	mlx_key_hook(mlx_win, key_hook, "message");
	mlx_put_image_to_window(mlx, mlx_win, img.img, 0, 0);
	mlx_loop(mlx);
}
