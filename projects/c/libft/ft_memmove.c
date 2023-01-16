/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:29:45 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/05 17:49:52 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t count)
{
	size_t				i;
	unsigned char		*tmp_dest;
	const unsigned char	*tmp_src;

	if (!dest && !src)
		return (NULL);
	i = 0;
	tmp_dest = (unsigned char *)dest;
	tmp_src = (const unsigned char *)src;
	if (tmp_dest > tmp_src)
	{
		while (++i <= count)
		{
			tmp_dest[count - i] = tmp_src[count - i];
		}
	}
	else
	{
		while (count-- > 0)
		{
			tmp_dest[i] = tmp_src[i];
			i++;
		}
	}
	return (tmp_dest);
}
