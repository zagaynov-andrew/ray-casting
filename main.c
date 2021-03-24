/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/21 12:36:22 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/24 07:49:30 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <mlx.h>

// # define CUB_SIZE 64

// typedef struct		s_img
// {
// 	void			*img;
// 	char			*addr;
// 	int				bits_per_pixel;
// 	int				size_line;
// 	int				width;
// 	int				height;
// 	int				endian;
// }					t_img;

// typedef struct		s_game
// {
// 	void			*mlx;
// 	void			*win;
// 	t_img			*img;
// 	int				last_side;
// 	int				last_depth;
// 	int				cur_depth;
// 	float			cur_ray_angle;
// }					t_game;

// typedef struct		s_vec2
// {
// 	int				x;
// 	int				y;
// }					t_vec2;

// typedef struct		s_vec2f
// {
// 	float			x;
// 	float			y;
// }					t_vec2f;

// unsigned int	get_pixel_color(t_img *img, int x, int y)
// {
// 	char *dst;

// 	if (x < 0 || y < 0)
// 		return (0);
// 	if (x >= img->width || y >= img->height)
// 		return (0);
// 	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
// 	return (*(unsigned int*)dst);
// }

// void	pixel_put(t_img *img, int x, int y, int color)
// {
// 	char	*dst;

// 	if (x >= img->width || y >= img->height)
// 		return ;
// 	if (x < 0 || y < 0)
// 		return ;
// 	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
// 	*(unsigned int*)dst = color;
// }

// void			draw_texture_line(t_game *game, t_vec2 win_point, t_vec2 info)
// {
// 	t_vec2f	tex_pos;
// 	int		height;
// 	float	step;
// 	int		i;
// 	t_img	tex;

// 	tex_pos.x = (float)info.x;
// 	tex_pos.y = 0;
// 	height = info.y;
// 	printf("%i\n",  game->img->height);
// 	win_point.y -= height / 2;
// 	step = (float)CUB_SIZE / height;

// 	tex.img = mlx_xpm_file_to_image(game->mlx, "./WALL33.xpm", &tex.width, &tex.height);
// 	tex.addr = mlx_get_data_addr(tex.img, &tex.bits_per_pixel, &tex.size_line,
// 							&tex.endian);

// 	i = 0;
// 	while (i < height)
// 	{
// 		pixel_put(game->img, win_point.x, win_point.y + i,
// 						get_pixel_color(&tex, (int)tex_pos.x, (int)tex_pos.y));
// 		tex_pos.y += step;
// 		i++;
// 	}
// }


#include <stdlib.h>
#include <stdio.h>
#include "libs/libft/libft.h"

void merge(t_vec *A,int p,int q,int r);
void part(t_vec *A,int p,int r);

int main()
{
	int a1 = 10;
	int a2 = 5;
	int a3 = 4;
	int a4 = 0;
	int a5 = 11;
	int a6 = 7;
	
	t_vec *A = ft_vec_new(6);
	ft_vec_push(&A, &a1);
	ft_vec_push(&A, &a2);
	ft_vec_push(&A, &a3);
	ft_vec_push(&A, &a4);
	ft_vec_push(&A, &a5);
	ft_vec_push(&A, &a6);
	int	n,y,z;
    y=0;
	z = 6;
    part(A,y,z);
    for(n=0;n<z;n++)
	{
		int *p;
		p = (int*)A->data[n];
        printf("%d\n", *p);
	}
    return 0;
}

void part(t_vec *A, int p, int r)
{
int q;
    if ((r - p) < 2)
        return;
    q = (p + r) / 2;
    part(A, p, q);
    part(A, q, r);
    merge(A, p, q, r);
}

void merge(t_vec *A, int p, int q, int r)
{
	int	n1 = q - p;
	int	n2 = r - q;
	int i, j, k;

	t_vec *L = ft_vec_new(n1);
	t_vec *R = ft_vec_new(n2);
    for (i=0; i < n1; i++)
        L->data[i] = A->data[p + i];
    for (j=0; j<n2; j++)
        R->data[j]= A->data[q + j];
    i=0;j=0;
    for(k = p; k < r; k++)
        if(j >= n2 || i < n1 && *(int*)(L->data[i]) <= *(int*)(R->data[j]))
            A->data[k] = L->data[i++];
        else
            A->data[k] = R->data[j++];
}
