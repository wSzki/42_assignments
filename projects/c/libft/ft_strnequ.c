/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnequ.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/30 19:12:25 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/04 15:55:41 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strnequ(char const *s1, char const *s2, size_t n)
{
	size_t i;

	if (s1 && s2)
	{
		if (n == 0)
			return (1);
		i = 0;
		while (*s1 && *s2 && *s1 == *s2 && i < n)
		{
			i++;
			if (i == n)
				break ;
			s1++;
			s2++;
		}
		if (*s1 == *s2)
			return (1);
	}
	return (0);
}
