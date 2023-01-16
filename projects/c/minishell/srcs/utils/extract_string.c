/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_string.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 01:41:57 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/20 16:19:32 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*extract_string(char *str, int len)
{
	char	*res;
	int		i;

	i = 0;
	if (len == -1)
		len = ft_strlen(str);
	res = malloc(sizeof(char) * (len + 1));
	if (!(res))
		return (NULL);
	while (str[i] && i < len)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
