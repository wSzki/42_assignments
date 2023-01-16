/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_whitespace.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:49:03 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/20 16:20:27 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_it_whitespace(char *str)
{
	int		i;
	char	*whitespaces;

	i = 0;
	whitespaces = " \t\r\v";
	while (whitespaces[i])
	{
		if (whitespaces[i] == str[0])
			return (YES);
		i++;
	}
	return (NO);
}

int	is_whitespace(char c)
{
	int		i;
	char	*whitespaces;

	i = -1;
	whitespaces = " \t\r\v";
	while (whitespaces[++i])
	{
		if (whitespaces[i] == c)
			return (YES);
	}
	return (NO);
}
