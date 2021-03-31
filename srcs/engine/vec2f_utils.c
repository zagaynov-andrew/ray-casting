/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/22 21:28:00 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:05:57 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void			vec2f_normalize(t_vec2f *vec)
{
	float len;

	len = vec2f_length(vec);
	vec->x = vec->x / len;
	vec->y = vec->y / len;
}

void			vec2f_multiply(t_vec2f *vec, float num)
{
	vec->x *= num;
	vec->y *= num;
}

t_vec2f			*vec2f_rotate(t_vec2f *vec, float angle)
{
	t_vec2f	tmp;

	tmp.x = vec->x * cos(angle) + vec->y * sin(angle);
	tmp.y = -vec->x * sin(angle) + vec->y * cos(angle);
	vec->x = tmp.x;
	vec->y = tmp.y;
	return (vec);
}
