/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/25 10:31:25 by wszurkow          #+#    #+#             */
/*   Updated: 2020/11/25 13:43:26 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *ptr, int ch, size_t count)
{
	unsigned char *tmp;

	tmp = (unsigned char*)ptr;
	while (count > 0)
	{
		if (*tmp != (unsigned char)ch)
			tmp++;
		else
			return (tmp);
		count--;
	}
	return (NULL);
}
