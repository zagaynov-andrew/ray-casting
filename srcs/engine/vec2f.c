/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:23:56 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/22 21:28:42 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float			vec2f_length(const t_vec2f *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y));
}

void			vec2f_change_length(t_vec2f *vec, float length)
{
	vec2f_normalize(vec);
	vec2f_multiply(vec, length);
}

t_vec2f			*vec2f_cpy(t_vec2f *dst, const t_vec2f *src)
{
	dst->x = src->x;
	dst->y = src->y;
	return (dst);
}

t_vec2f			*vec2f_init(t_vec2f *vec, float x, float y)
{
	vec->x = x;
	vec->y = y;
	return (vec);
}

t_vec2			*vec2f_to_vec2(t_vec2 *dst, const t_vec2f *src)
{
	dst->x = (int)round(src->x);
	dst->y = (int)round(src->y);
	return (dst);
}
