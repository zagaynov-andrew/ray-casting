/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:38:16 by nforce            #+#    #+#             */
/*   Updated: 2021/03/18 09:24:14 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs/gnl/get_next_line.h"
# include "libs/libft/libft.h"
# include "cub3d_errors.h"
# include "libs/minilibx-linux/mlx.h"
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# include <stdio.h> //

# define RED 0
# define GREEN 1
# define BLUE 2
# define MAP_SET "012NSEW"
# define SPACE '0'
# define WALL '1'
# define SPRITE '2'

# define CUB_SIZE 32
# define NUM_RAYS 50
# define FOV 1.05
# define RAY_LEN 200

typedef struct		s_point
{
	int				x;
	int				y;
}					t_point;

typedef	struct		s_scene
{
	int				width;
	int				height;
	char			*no;
	char			*so;
	char			*we;
	char			*ea;
	char			*s;
	unsigned int	f;
	unsigned int	c;
	t_vec			*map;
	char			start_pos_flag;
	int				empty_line;
}					t_scene;

t_scene				*parse_cub(char *path);

t_scene				*scene_new(void);
void				free_scene(t_scene	*scene);

int					is_full_configs(t_scene *scene);
void				read_remain(int fd);
int					push_new_map_line(char *line, t_scene *scene);
int					parse_line_one_letter(char *line, t_scene *scene);
int					parse_line_two_letters(char *line, t_scene *scene);

int					parse_r(char *str, t_scene *scene);
int					parse_fc(char *str, unsigned int *color);
int					parse_texture_path(char *str, char **path);

int					is_valid_path(char *path);
int					next_value(char **str, int value);
int					color_component(char **str, int component,
													unsigned int *color);
char				*pass_whitespaces(char **str);

int					is_valid_map_row(char *line, t_scene *scene);
int					is_valid_map_column(t_vec *map);

t_vec				*get_rectangular_map(t_vec *map);

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

typedef struct		s_player
{
	t_point			pos;
	float			cam_angle;
}					t_player;

typedef struct		s_game
{
	t_scene			*scene;
	t_player		*player;
	t_img			*img;
}					t_game;


void	pixel_put(t_img *img, int x, int y, int color);
void	draw_line(t_img *img, t_point* begin, t_vec2* vec, int color);
void	draw_square(t_img *img, t_point *p0, int size, int color);
void	rotate(t_vec2 *vec, float angle);
void	set_start_position(t_player *player, t_vec *map);
void	draw_square_centre(t_img *img, t_point *p0, int size, int color);
void			cut_line(t_game *game, t_vec2 *ray_dir);
void			draw_rays(t_game *game, int color);
float			get_side_dist_x(const t_player *player, const t_vec2 *ray_dir, float delta_dist_x);
float			get_side_dist_y(const t_player *player, const t_vec2 *ray_dir, float delta_dist_y);
float			get_delta_dist_x(const t_vec2 *ray_dir);
float			get_delta_dist_y(const t_vec2 *ray_dir);
float			lenght(const t_vec2f *vec);
void			normalize(t_vec2f *vec);
void			multiply(t_vec2f *vec, float num);
void			vec2_change_length(t_vec2 *vec, float length);
void			to_vec2(t_vec2 *vec2, t_vec2f *vec2f, float length);
void			vec2_cpy(t_vec2 *dst, const t_vec2 *src);
void	draw_grid(t_img *img, int color);

#endif
