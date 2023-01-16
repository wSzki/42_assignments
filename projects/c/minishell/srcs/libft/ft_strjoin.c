/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 13:36:51 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/01 18:11:08 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*res;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char *)s1) + ft_strlen((char *)s2);
	res = (char *)malloc(sizeof(char) * len + 1);
	if (!(res))
		error_management("", errno);
	if (s1 && s2)
	{
		while (s1[i])
			res[j++] = s1[i++];
		i = 0;
		while (s2[i])
			res[j++] = s2[i++];
		res[j] = '\0';
	}
	return (res);
}
