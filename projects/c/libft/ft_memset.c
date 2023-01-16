/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 13:58:50 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/05 17:48:01 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *dest, int ch, size_t count)
{
	size_t				i;
	unsigned char		*tmp_dest;

	tmp_dest = (unsigned char *)dest;
	i = -1;
	while (++i < count)
	{
		*tmp_dest = (unsigned char)ch;
		tmp_dest++;
	}
	return (dest);
}
