/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 16:58:22 by wszurkow          #+#    #+#             */
/*   Updated: 2020/12/05 15:13:37 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_is_set(const char c, const char *set)
{
	int i;

	i = -1;
	while (set[++i])
		if (set[i] == c)
			return (1);
	return (0);
}

char		*ft_strtrim(const char *s1, const char *set)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	*str;

	if (!s1)
		return (NULL);
	i = -1;
	j = 0;
	len = ft_strlen(s1);
	while (ft_is_set(s1[len - 1], set) && len > 0)
		len--;
	while (ft_is_set(s1[++i], set) && s1[i] && len > 0)
		len--;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (0);
	while (j < len)
	{
		str[j] = s1[i];
		i++;
		j++;
	}
	str[j] = '\0';
	return (str);
}
