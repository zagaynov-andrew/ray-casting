/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/27 19:25:03 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:06:08 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	max_map_row_len(t_vec *map)
{
	int		max_len;
	int		cur_len;
	int		i;

	if (!map)
		return (-1);
	i = 0;
	max_len = 0;
	while (i < (int)map->size)
	{
		if ((cur_len = ft_strlen(map->data[i])) > max_len)
			max_len = cur_len;
		i++;
	}
	return (max_len);
}

t_vec		*get_rectangular_map(t_vec *map)
{
	t_vec	*tmp;
	char	*new;
	int		max_len;
	int		cur_len;
	int		i;

	if (!map)
		return (NULL);
	if ((max_len = max_map_row_len(map)) <= 0)
		return (NULL);
	if (!(tmp = ft_vec_new(map->size)))
		return (NULL);
	i = -1;
	while (++i < (int)map->size)
	{
		if (!(new = ft_calloc(max_len + 1, sizeof(char))))
			return (NULL);
		ft_strlcpy(new, (map->data)[i], max_len + 1);
		cur_len = ft_strlen((map->data)[i]);
		ft_memset((void*)new + cur_len, ' ', max_len - cur_len);
		if (!ft_vec_push(&tmp, (void*)new))
			return (NULL);
	}
	return (tmp);
}
