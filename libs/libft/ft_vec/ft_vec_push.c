/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 00:08:40 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 00:23:32 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_vec.h"

static t_vec	*ft_vec_realloc(t_vec *vec)
{
	void	**new;
	int		i;

	if (!vec)
		return (NULL);
	if (!(new = ft_calloc(vec->capacity * 2, sizeof(void*))))
		return (NULL);
	i = 0;
	while (i < (int)vec->size)
	{
		new[i] = (vec->data)[i];
		i++;
	}
	free(vec->data);
	vec->data = new;
	vec->capacity *= 2;
	return (vec);
}

void			ft_vec_push(t_vec **vec, void *new)
{
	if (!vec)
		return ;
	if ((*vec)->size < (*vec)->capacity)
		((*vec)->data)[(*vec)->size] = new;
	else
	{
		ft_vec_realloc(*vec);
		((*vec)->data)[(*vec)->size] = new;
	}
	(*vec)->size++;
}
