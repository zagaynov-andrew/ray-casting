/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/24 16:38:16 by nforce            #+#    #+#             */
/*   Updated: 2021/01/26 17:42:49 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "libs/gnl/get_next_line.h"
# include "libs/libft/libft.h"
# include <fcntl.h>
# include <errno.h>

# define RED 0
# define GREEN 1
# define BLUE 2

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
}					t_scene;

t_scene				*scene_new(void);
void				free_scene(t_scene	*scene);
t_scene				*parse_cub(char *path);
int					parse_line(char *line, t_scene *scene);

int					parse_r(char *str, t_scene *scene);
int					next_value(char **str, int value);
int					parse_fc(char *str, unsigned int *color);
int					color_component(char **str, int component, int *color);
int					get_color(unsigned int *color, int component, int value);
int					parse_texture_path(char *str, char **path);
int					is_valid_path(char *path);
int					is_full_configs(t_scene *scene);
int					parse_line_one_letter(char *line, t_scene *scene);
int					parse_line_two_letters(char *line, t_scene *scene);

#endif