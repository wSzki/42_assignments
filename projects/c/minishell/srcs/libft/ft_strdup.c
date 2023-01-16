/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/22 15:46:09 by adlancel          #+#    #+#             */
/*   Updated: 2021/11/01 18:11:19 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*ft_strdup(const char *s1)
{
	char		*copy;
	size_t		i;

	i = -1;
	if (!s1)
		return (NULL);
	copy = malloc(sizeof(char) * ft_strlen(s1) + 1);
	if (!copy)
		error_management("", errno);
	while (++i < ft_strlen(s1))
		copy[i] = s1[i];
	copy[i] = '\0';
	return (copy);
}
