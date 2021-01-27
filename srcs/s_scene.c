/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   s_scene.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 17:43:11 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 15:38:32 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
	scene->start_pos = 0;
	scene->empty_line = 0;
	if (!(scene->map = ft_vec_new(8)))
		return (NULL);
	return (scene);
}

void	ft_vec_data_free(void **data, size_t size)
{
	int	i;

	if (!data)
		return ;
	i = 0;
	while (i < (int)size)
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	ft_vec_free(t_vec *vec)
{
	if (!vec)
		return ;
	ft_vec_data_free(vec->data, vec->size);
	free(vec);
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
	if (scene->map != NULL)
		ft_vec_free(scene->map);
	free(scene);
}
