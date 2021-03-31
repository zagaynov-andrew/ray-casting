/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_overflow.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ngamora <ngamora@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/31 14:13:28 by ngamora           #+#    #+#             */
/*   Updated: 2021/03/31 15:06:06 by ngamora          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int			int_overflow_positive(const char *str)
{
	char	*max;
	int		i;
	int		num_len;

	if (!(max = ft_strdup("2147483647")))
	{
		errno = ENOMEM;
		return (-1);
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] <= max[i] && str && max)
		i++;
	num_len = i;
	while (str[num_len] >= '0' && str[num_len] <= '9')
		num_len++;
	if (ft_isdigit(str[i]) != 1)
		i--;
	if (str[i] > max[i] && num_len >= ft_strlen(max))
	{
		free(max);
		return (1);
	}
	free(max);
	return (0);
}

int			int_overflow_negative(const char *str)
{
	char	*min;
	int		i;
	int		num_len;

	if (!(min = ft_strdup("2147483648")))
	{
		errno = ENOMEM;
		return (-1);
	}
	i = 0;
	while (str[i] >= '0' && str[i] <= '9' && str[i] <= min[i] && str && min)
		i++;
	num_len = i;
	while (str[num_len] >= '0' && str[num_len] <= '9')
		num_len++;
	if (ft_isdigit(str[i]) != 1)
		i--;
	if (str[i] > min[i] && num_len >= ft_strlen(min))
	{
		free(min);
		return (2);
	}
	free(min);
	return (0);
}

int			int_overflow(const char *str)
{
	int i;
	int flag;

	i = 0;
	flag = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		flag = 1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	if (flag == 0)
		return (int_overflow_positive(str + i));
	else
		return (int_overflow_negative(str + i));
}

int			check_int_overflow(const char *str)
{
	int	overflow;

	overflow = int_overflow(str);
	if (overflow == -1)
		return (-1);
	if (overflow == 1)
		return (1);
	if (overflow == 2)
	{
		errno = ERR_RESOLUTION;
		return (-1);
	}
	return (0);
}
