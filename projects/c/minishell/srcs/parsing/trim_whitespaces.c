/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_whitespaces.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:40:59 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/20 15:45:41 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*trim_prepending_whitespaces(char *str)
{
	int		i;
	char	*res;

	i = 0;
	while (str[i] && (
			str[i] == '\t'
			|| str[i] == '\r'
			|| str[i] == '\v'
			|| str[i] == ' '))
		i++;
	res = extract_string(&str[i], FULL_LENGTH);
	free(str);
	str = NULL;
	return (res);
}

static char	*trim_appending_whitespaces(char *str)
{
	int		len;
	char	*res;

	len = ft_strlen(str) - 1;
	while (len > 0 && (
			str[len] == '\t'
			|| str[len] == '\r'
			|| str[len] == '\v'
			|| str[len] == ' '))
		len--;
	len++;
	res = extract_string(str, len);
	free(str);
	str = NULL;
	return (res);
}

char	**trim_whitespaces(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (i % 2 == 0)
		{
			tab[i] = trim_prepending_whitespaces(tab[i]);
			tab[i] = trim_appending_whitespaces(tab[i]);
		}
	}
	return (tab);
}
