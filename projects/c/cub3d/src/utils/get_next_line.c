/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 00:26:41 by wszurkow          #+#    #+#             */
/*   Updated: 2022/05/01 00:26:44 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_realloc(char *line, int *i)
{
	int		l;
	char	*str;

	l = 0;
	str = malloc(*i * 2);
	if (str == NULL)
		return (NULL);
	*i *= 2;
	while (line && line[l])
	{
		str[l] = line[l];
		l++;
	}
	while (l < *i)
	{
		str[l] = 0;
		l++;
	}
	free(line);
	return (str);
}

static int	resize_container(int i, char **line, int *malloc_size)
{
	if (i == *malloc_size - 2)
	{
		*line = ft_realloc(*line, malloc_size);
		if (!(*line))
			return (-1);
	}
	return (0);
}

int	get_next_line(int fd, char **line)
{
	int	r;
	int	i;
	int	malloc_size;

	r = 1;
	i = -1;
	malloc_size = 50;
	if (!line)
		return (-1);
	*line = NULL;
	*line = ft_realloc(*line, &malloc_size);
	if (*line == 0)
		return (-1);
	while (1)
	{
		r = read(fd, &(*line)[++i], 1);
		if (r == 0 || (*line)[i] == 10)
			break ;
		if (resize_container(i, line, &malloc_size) == -1)
			return (-1);
	}
	(*line)[i] = 0;
	return (r);
}
