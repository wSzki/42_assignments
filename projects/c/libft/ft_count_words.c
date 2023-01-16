/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_count_words.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/07 15:04:46 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/07 15:57:11 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_count_words(const char *str, char c)
{
	size_t	i;
	size_t	words;

	if (!str)
		return (0);
	i = 0;
	words = 0;
	while (str[i] == c)
		i++;
	while (str[i])
	{
		while (str[i] && str[i] != c)
			i++;
		words++;
		while (str[i] && str[i] == c)
			i++;
	}
	return (words);
}
