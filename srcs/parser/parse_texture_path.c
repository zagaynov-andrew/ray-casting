/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:40:08 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:06:19 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	parse_after_texture_path(char *begin, char *after, char **path)
{
	char	*end;

	end = after;
	pass_whitespaces(&after);
	if (!*after)
	{
		*end = '\0';
		if ((is_valid_path(begin)) == -1)
			return (-1);
		*path = ft_strdup(begin);
		return (1);
	}
	errno = ERR_EXTRA_CHAR_AFTER;
	return (-1);
}

int			parse_texture_path(char *str, char **path)
{
	char	*ptr;

	if (*path)
	{
		errno = ERR_RE_CONFIG;
		return (-1);
	}
	pass_whitespaces(&str);
	if (!(ptr = ft_strnstr(str, ".xpm", ft_strlen(str))))
	{
		if (!(ptr = ft_strnstr(str, ".png", ft_strlen(str))))
		{
			errno = ERR_EXTEN_TEXTURE;
			return (-1);
		}
	}
	ptr += 4;
	return (parse_after_texture_path(str, ptr, path));
}
