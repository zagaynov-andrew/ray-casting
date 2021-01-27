/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vec.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/26 20:12:51 by nforce            #+#    #+#             */
/*   Updated: 2021/01/27 13:42:05 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_VEC_H
# define FT_VEC_H

# include "libft.h"
# include <stddef.h>

typedef	struct	s_vec
{
	void		**data;
	size_t		size;
	size_t		capacity;
}				t_vec;

t_vec			*ft_vec_new(size_t capacity);
void			ft_vec_data_free(void **data, size_t size);
void			ft_vec_free(t_vec *vec);
t_vec			*ft_vec_push(t_vec **vec, void *new);

#endif
