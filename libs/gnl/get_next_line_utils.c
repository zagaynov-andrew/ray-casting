/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nforce <nforce@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 13:01:17 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/24 16:06:42 by nforce           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	int	src_len;
	int	i;

	if (!dst || !src)
		return (0);
	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;
	if (dstsize == 0)
		return (src_len);
	i = 0;
	while (i < src_len && i < (int)dstsize - 1)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

char	*ft_strjoin_free(char *s1, char const *s2)
{
	char	*newstr;
	int		s1_len;
	int		s2_len;

	if (!s1 || !s2)
		return (NULL);
	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	s2_len = 0;
	while (s2[s2_len] != '\0')
		s2_len++;
	newstr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!newstr)
		return (NULL);
	ft_strlcpy(newstr, s1, s1_len + s2_len + 1);
	ft_strlcpy(&newstr[s1_len], s2, s2_len + 1);
	free(s1);
	s1 = NULL;
	return (newstr);
}

char	*ft_strdup(const char *s1)
{
	char	*s2;
	int		s1_len;

	s1_len = 0;
	while (s1[s1_len] != '\0')
		s1_len++;
	s2 = (char*)malloc(s1_len + 1);
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s1, s1_len + 1);
	return (s2);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	s_len;

	if (!s)
		return (NULL);
	i = 0;
	s_len = 0;
	while (s[s_len] != '\0')
		s_len++;
	while (i < s_len + 1)
	{
		if (s[i] == (char)c)
			return ((char*)(s + i));
		i++;
	}
	return (NULL);
}
