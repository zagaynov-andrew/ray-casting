/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:43:11 by nforce            #+#    #+#             */
/*   Updated: 2021/01/26 18:36:49 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

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
	return (scene);
}

void	free_scene(t_scene *scene)
{
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
	free(scene);
}
