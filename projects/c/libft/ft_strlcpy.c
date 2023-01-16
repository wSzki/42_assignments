/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:56:53 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/04 16:03:18 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t		ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t j;
	size_t i;

	i = 0;
	j = 0;
	if (dest || src)
	{
		while ((src[i]) && (i + 1 < size))
		{
			dest[i] = src[i];
			i++;
		}
		if (size > 0)
			dest[i] = '\0';
		while (src[j])
			j++;
	}
	return (j);
}
