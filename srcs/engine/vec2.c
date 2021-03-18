/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:30 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/18 22:58:59 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

float			lenght(const t_vec2f *vec)
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

	len = lenght(vec);
	vec->x = vec->x / len;
	vec->y = vec->y / len;
}

void			multiply(t_vec2f *vec, float num)
{
	vec->x *= num;
	vec->y *= num;
}

void			vec2_change_length(t_vec2 *vec, float length)
{
	t_vec2f	vec2f;

	vec2f.x = (float)vec->x;
	vec2f.y = (float)vec->y;
	normalize(&vec2f);
	multiply(&vec2f, length);
	vec->x = (int)round(vec2f.x);
	vec->y = (int)round(vec2f.y);
}

void			vec2_cpy(t_vec2 *dst, const t_vec2 *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

void			vec2_init(t_vec2 *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}