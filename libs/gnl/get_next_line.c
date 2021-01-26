/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/25 17:34:29 by nforce            #+#    #+#             */
/*   Updated: 2021/01/26 18:06:30 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		processing_remainder(char **remainder, char **line)
{
	char	*p_endl;
	char	*tmp;

	if (!(*line = ft_strdup("")))
		return (-1);
	if ((p_endl = ft_strchr(*remainder, '\n')))
	{
		*p_endl = '\0';
		if (!(*line = ft_strjoin_free(*line, *remainder)))
			return (-1);
		tmp = *remainder;
		if (!(*remainder = ft_strdup(p_endl + 1)))
			return (-1);
		free(tmp);
		return (0);
	}
	else if (*remainder)
	{
		if (!(*line = ft_strjoin_free(*line, *remainder)))
			return (-1);
		free(*remainder);
		*remainder = NULL;
	}
	return (1);
}

int		get_next_line_main(int fd, char **line, char *buf)
{
	static	char	*remainder;
	char			*p_endl;
	int				ret;

	if ((ret = processing_remainder(&remainder, line)) <= 0)
		return (ret == -1 ? -1 : 1);
	while ((ret = read(fd, buf, BUFFER_SIZE)))
	{
		buf[ret] = '\0';
		if ((p_endl = ft_strchr(buf, '\n')))
		{
			*p_endl = '\0';
			if (!(*line = ft_strjoin_free(*line, buf)))
				return (-1);
			if (!(remainder = ft_strdup(p_endl + 1)))
				return (-1);
			return (1);
		}
		if (!(*line = ft_strjoin_free(*line, buf)))
			return (-1);
	}
	return (ret ? 1 : 0);
}

int		get_next_line(int fd, char **line)
{
	char			*buf;
	int				ret;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	if (!(buf = (char*)malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	if (read(fd, buf, 0) < 0)
	{
		free(buf);
		return (-1);
	}
	ret = get_next_line_main(fd, line, buf);
	free(buf);
	return (ret);
}
