/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 15:54:47 by wszurkow          #+#    #+#             */
/*   Updated: 2021/12/12 15:09:35 by wsz              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static void	fetch_char_range(t_global *g, unsigned int c)
{
	if (c < g->smallest_char)
		g->smallest_char = c;
	if (c > g->largest_char)
		g->largest_char = c;
}

char	*ft_strdup(t_global *g, const char *src)
{
	int		i;
	char	*ptr;

	i = 0;
	if (src == NULL)
		return (NULL);
	while (src[i])
		i++;
	ptr = (char *)malloc(sizeof(char) * i + 1);
	if (!ptr)
	{
		g->status = errno;
		return (NULL);
	}
	i = -1;
	while (src[++i])
	{
		ptr[i] = src[i];
		fetch_char_range(g, src[i]);
	}
	ptr[i] = '\0';
	return (ptr);
}
