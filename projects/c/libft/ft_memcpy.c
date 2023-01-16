/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/16 23:23:03 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/04 17:46:39 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t count)
{
	size_t	i;
	void	*tmp;

	if (!dest && !src)
		return (NULL);
	tmp = dest;
	i = -1;
	while (++i < count)
		*(unsigned char *)dest++ = *(unsigned char *)src++;
	return (tmp);
}
