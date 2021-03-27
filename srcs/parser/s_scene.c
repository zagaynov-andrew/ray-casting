/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:43:11 by nforce            #+#    #+#             */
/*   Updated: 2021/03/27 10:02:17 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

t_scene	*scene_new(void)
{
	t_scene	*scene;

	if (!(scene = (t_scene*)malloc(sizeof(t_scene))))
		return (NULL);
	scene->width = -1;
	scene->height = -1;
	scene->no = NULL;
	scene->so = NULL;
	scene->we = NULL;
	scene->ea = NULL;
	scene->s = NULL;
	scene->f = 0x1000000;
	scene->c = 0x1000000;
	scene->start_pos_flag = ' ';
	scene->empty_line = 0;
	if (!(scene->map = ft_vec_new(8)))
		return (NULL);
	return (scene);
}

void	free_scene(t_scene *scene)
{
	if (scene == NULL)
		return ;
	if (scene->no != NULL)
		free(scene->no);
	if (scene->so != NULL)
		free(scene->so);
	if (scene->we != NULL)
		free(scene->we);
	if (scene->ea != NULL)
		free(scene->ea);
	if (scene->s != NULL)
		free(scene->s);
	if (scene->map != NULL)
		ft_vec_free(scene->map);
	free(scene);
}
