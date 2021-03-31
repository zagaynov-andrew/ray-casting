/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:38:16 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:53:45 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libs/gnl/get_next_line.h"
# include "../libs/libft/libft.h"
# include "../libs/minilibx-linux/mlx.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>
# include <math.h>

# define RED		0
# define GREEN		1
# define BLUE		2
# define MAP_SET	"012NSEW"
# define SPACE		'0'
# define WALL		'1'
# define SPRITE		'2'

# define CUB_SIZE	512
# define EPSILON	20
# define FOV		1.15
# define RAY_LEN	200

# define KEY_W		119
# define KEY_S		115
# define KEY_A		97
# define KEY_D		100
# define KEY_LEFT	65361
# define KEY_RIGHT	65363
# define KEY_UP		65362
# define KEY_DOWN	65364
# define KEY_ESC	65307

# define STOP		0
# define TOWARD		1
# define BACKWARD	2
# define LEFT		4
# define RIGHT		8

# define COUNTERCLOCKWISE	1
# define CLOCKWISE			2
# define CAMERA_UP			4
# define CAMERA_DOWN		5

# define MOVEMENT_SPEED		1
# define ROTATION_SPEED		1

# define NOTHING	0
# define HORIZONTAL	1
# define VERTICAL	2

# define NO	1
# define SO	2
# define WE	3
# define EA	4

# define SUCCESS				0
# define ERR_ABS_START_POS		134
# define ERR_REP_START_POS		135
# define ERR_EXTRA_CHAR_BETWEEN	136
# define ERR_NO_MAP				137
# define ERR_EMPTY_LINE_MAP		138
# define ERR_NO_COMMA			139
# define ERR_RE_CONFIG			140
# define ERR_EXTRA_CHAR_AFTER	141
# define ERR_RESOLUTION			142
# define ERR_EXTEN_TEXTURE		143
# define ERR_TEXTURE_NOT_EXIST	144
# define ERR_EXTRA_CHAR			145
# define ERR_INVALID_COLOR		146
# define ERR_COLOR_CONFIG		147
# define ERR_NO_WALL			148
# define ERR_NO_COLOR			149
# define ERR_EXTRA_MAP			150

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
	t_vec2			pos;
	float			cam_angle;
	unsigned char	movement;
	unsigned char	rotation;
}					t_player;

typedef struct		s_game
{
	t_scene			*scene;
	t_player		player;
	void			*mlx;
	void			*win;
	t_img			img;
	float			cur_ray_angle;
	t_img			no;
	t_img			so;
	t_img			we;
	t_img			ea;
	t_img			s;
	t_vec			*sprites;
	float			*wall_depth;
	float			*angle;
	int				horizont;
}					t_game;

typedef struct		s_dda
{
	float			delta_dist_x;
	float			delta_dist_y;
	float			side_dist_x;
	float			side_dist_y;
}					t_dda;

typedef struct		s_sprite
{
	t_vec2			pos;
	float			depth;
	float			delta_angle;
	int				visible;
	t_vec2			dir;
}					t_sprite;

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
int					next_value(char **str);
int					color_component(char **str, int component,
													unsigned int *color);
char				*pass_whitespaces(char **str);

int					is_valid_map_row(char *line, t_scene *scene);
int					is_valid_map_column(t_vec *map);

t_vec				*get_rectangular_map(t_vec *map);

void				pixel_put(t_img *img, int x, int y, int color);
void				draw_line(t_img *img, t_vec2 *begin, t_vec2 *vec,
																int color);
void				draw_square(t_img *img, t_vec2 *p0, int size, int color);
void				vec2_rotate(t_vec2 *vec, float angle);
void				set_start_position(t_player *player, t_vec *map);
void				draw_square_centre(t_img *img, t_vec2 *p0, int size,
																	int color);
void				draw_rectangle(t_img *img, t_vec2 *begin, t_vec2 *end,
																	int color);
int					get_ray_dir(t_game *game, t_vec2f *ray_dir);
void				draw_walls(t_game *game);
float				get_side_dist_x(const t_player *player,
									const t_vec2f *ray_dir, float delta_dist_x);
float				get_side_dist_y(const t_player *player,
									const t_vec2f *ray_dir, float delta_dist_y);
float				get_delta_dist_x(const t_vec2f *ray_dir);
float				get_delta_dist_y(const t_vec2f *ray_dir);
float				vec2f_length(const t_vec2f *vec);
void				normalize(t_vec2f *vec);
void				multiply(t_vec2f *vec, float num);
void				vec2f_change_length(t_vec2f *vec, float length);
void				to_vec2(t_vec2 *vec2, t_vec2f *vec2f, float length);
void				vec2_cpy(t_vec2 *dst, const t_vec2 *src);
void				draw_grid(t_img *img, int color);
void				init_dda(t_dda *dda, const t_game *game,
													const t_vec2f *ray_dir);
void				init_player(t_player *player, t_scene *scene);
void				draw_map(t_img *img, t_vec *map);
int					key_pressed(int key_code, t_game *game);
int					key_released(int key_code, t_game *game);
int					exit_game(t_game *game);
int					render_frame(t_game *game);
void				img_clear(t_img *img);
int					is_wall(t_game *game, t_vec2 *ray_dir);
int					is_wall_no_epsilon(t_game *game, int x, int y);
int					is_barrier_around_point(t_game *game, int x, int y);
void				move_player(t_game *game);
void				rotate_player(t_game *game);
float				vec2_length(const t_vec2 *vec);
void				vec2_init(t_vec2 *vec, int x, int y);
int					get_side(t_game *game, t_vec2 *point);
int					is_corner(t_game *game, t_vec2 *point);
void				draw_vertical_line(t_img *img, t_vec2 *begin,
													t_vec2 *end, int color);
t_vec2				*vec2f_to_vec2(t_vec2 *dst, const t_vec2f *src);
t_vec2f				*vec2f_init(t_vec2f *vec, float x, float y);
t_vec2f				*vec2f_cpy(t_vec2f *dst, const t_vec2f *src);
t_vec2f				*vec2f_rotate(t_vec2f *vec, float angle);
void				vec2f_normalize(t_vec2f *vec);
void				vec2f_multiply(t_vec2f *vec, float num);
void				draw_texture_line(t_game *game, t_vec2 win_point,
											t_vec2 info, int texture_code);
int					init_game(t_game *game);
int					init_window(t_game *game, t_scene *scene);
void				init_textures(t_game *game);
void				cut_angle(float *angle);

void				sprite_set_data(t_game *game);
void				draw_sprites(t_game *game);
int					init_sprites(t_game *game);
void				save_bmp(t_game *game);
void				draw_floor(t_game *game);
void				draw_ceiling(t_game *game);

int					is_left_down_corner(t_game *game, t_vec2 *point);
int					is_right_up_corner(t_game *game, t_vec2 *point);
int					is_left_up_corner(t_game *game, t_vec2 *point);
int					is_right_down_corner(t_game *game, t_vec2 *point);

void				destroy_mlx_ptrs(t_game *game);
void				free_game(t_game *game);

void				sprites_sort(t_vec *sprites);
void				set_visible(t_game *game);

int					lower_cutoff(t_game *game, float *tex_pos_y, float step,
																	int height);
int					upper_cutoff(t_game *game, int height);
int					get_texture_offset_x(t_game *game, t_vec2f *ray_dir,
																	int side);
int					int_overflow_positive(const char *str);
int					int_overflow_negative(const char *str);
int					int_overflow(const char *str);
int					check_int_overflow(const char *str);

int					print_error_string(char *str);
int					print_error(void);

#endif
