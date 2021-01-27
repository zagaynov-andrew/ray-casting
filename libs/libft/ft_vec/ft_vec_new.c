/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:20:22 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 13:53:15 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../ft_vec.h"

t_vec	*ft_vec_new(size_t capacity)
{
	t_vec	*vec;

	if (!capacity)
		return (NULL);
	if (!(vec = ft_calloc(capacity, sizeof(t_vec))))
		return (NULL);
	if (!(vec->data = ft_calloc(capacity, sizeof(void*))))
		return (NULL);
	vec->size = 0;
	vec->capacity = capacity;
	return (vec);
}
