/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:30 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/21 14:34:10 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float			vec2f_length(const t_vec2f *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y));
}

float			vec2_length(const t_vec2 *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y));
}

void			normalize(t_vec2f *vec)
{
	float len;

	len = vec2f_length(vec);
	vec->x = vec->x / len;
	vec->y = vec->y / len;
}

void			multiply(t_vec2f *vec, float num)
{
	vec->x *= num;
	vec->y *= num;
}

void			vec2f_change_length(t_vec2f *vec, float length)
{
	normalize(vec);
	multiply(vec, length);
}

void			vec2_cpy(t_vec2 *dst, const t_vec2 *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

t_vec2f			*vec2f_cpy(t_vec2f *dst, const t_vec2f *src)
{
	dst->x = src->x;
	dst->y = src->y;
	return (dst);
}

void			vec2_init(t_vec2 *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
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

t_vec2f			*vec2f_rotate(t_vec2f *vec, float angle)
{
	t_vec2f	tmp;

	tmp.x = vec->x * cos(angle) + vec->y * sin(angle);
	tmp.y = - vec->x * sin(angle) + vec->y * cos(angle);
	vec->x = tmp.x;
	vec->y = tmp.y;
	return (vec);
}
