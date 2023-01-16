/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/09 16:07:53 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/28 02:43:48 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
		i++;
	return (i);
}

int		find_n(char *str)
{
	int	i;

	if (!str)
		return (-1);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	return (-1);
}

void	*ft_calloc(size_t count, size_t size)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!(res = (char *)malloc(count * size)))
		return (NULL);
	while (i < count)
	{
		res[i] = 0;
		i++;
	}
	return (res);
}

char	*ft_substr(char const *str, unsigned int start, int len)
{
	int		i;
	char	*res;

	if (len == -1)
		len = ft_strlen(str);
	if (!str)
		return (NULL);
	if (!(res = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	i = 0;
	if (start < ft_strlen(str))
	{
		while (str[start] && i < len)
		{
			res[i] = str[start];
			i++;
			start++;
		}
	}
	res[i] = '\0';
	return (res);
}

char	*ft_gnl_strjoin(char *static_str, char *buffer, int read_value)
{
	size_t	i;
	size_t	j;
	char	*res;

	buffer[read_value] = '\0';
	i = ft_strlen(static_str);
	j = ft_strlen(buffer);
	if (!(res = (char *)malloc(sizeof(char) * (i + j + 1))))
		return (NULL);
	i = -1;
	while (static_str[++i])
		res[i] = static_str[i];
	j = -1;
	while (buffer[++j])
		res[i++] = buffer[j];
	res[i] = '\0';
	free(static_str);
	static_str = NULL;
	return (res);
}
