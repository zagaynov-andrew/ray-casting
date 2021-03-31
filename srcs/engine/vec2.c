/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/18 10:26:30 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:05:54 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	vec2_length(const t_vec2 *vec)
{
	return (sqrtf(vec->x * vec->x + vec->y * vec->y));
}

void	vec2_cpy(t_vec2 *dst, const t_vec2 *src)
{
	dst->x = src->x;
	dst->y = src->y;
}

void	vec2_init(t_vec2 *vec, int x, int y)
{
	vec->x = x;
	vec->y = y;
}

void	vec2_rotate(t_vec2 *vec, float angle)
{
	t_vec2	tmp;

	tmp.x = (int)round(vec->x * cos(angle) + vec->y * sin(angle));
	tmp.y = (int)round(-vec->x * sin(angle) + vec->y * cos(angle));
	vec->x = tmp.x;
	vec->y = tmp.y;
}
