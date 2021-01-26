/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/27 13:02:19 by ngamora           #+#    #+#             */
/*   Updated: 2021/01/20 14:11:39 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

typedef	struct		s_rmd
{
	int				fd;
	char			*str;
	struct s_rmd	*next;
}					t_rmd;

size_t				ft_strlcpy(char *dst, const char *src, size_t dstsize);
char				*ft_strdup(const char *s1);
char				*ft_strchr(const char *s, int c);
char				*ft_strjoin_free(char *s1, char const *s2);

int					processing_remainder(char **remainder, char **line);
int					get_next_line(int fd, char **line);
int					get_next_line_main(int fd, char **line, char *buf);

#endif
