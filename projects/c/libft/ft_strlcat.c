/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:57:06 by wszurkow          #+#    #+#             */
/*   Updated: 2020/10/14 16:27:32 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t src_size;
	size_t dest_size;
	size_t i;

	src_size = ft_strlen(src);
	dest_size = ft_strlen(dest);
	if (size == 0)
		return (src_size);
	i = 0;
	while (src[i] && i + dest_size + 1 < size)
	{
		dest[dest_size + i] = src[i];
		i++;
	}
	if (dest_size > size)
	{
		return (src_size + size);
	}
	else
	{
		dest[dest_size + i] = '\0';
	}
	return (src_size + dest_size);
}
