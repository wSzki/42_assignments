/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:31:56 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/04 17:48:12 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (*(unsigned char *)(src + i) == (unsigned char)c)
		{
			*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
			i++;
			return ((unsigned char *)dest + i);
		}
		*(unsigned char *)(dest + i) = *(unsigned char *)(src + i);
		i++;
	}
	return (NULL);
}
