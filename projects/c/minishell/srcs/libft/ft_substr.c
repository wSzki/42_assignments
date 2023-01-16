/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:53:24 by adlancel          #+#    #+#             */
/*   Updated: 2021/10/21 17:18:37 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	i = 0;
	if (!s)
		return (NULL);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!(res))
		error_management("", errno);
	if (start < ft_strlen(s))
	{
		while (s[start] && i < len)
		{
			res[i] = s[start];
			i++;
			start++;
		}
	}
	res[i] = '\0';
	return (res);
}
