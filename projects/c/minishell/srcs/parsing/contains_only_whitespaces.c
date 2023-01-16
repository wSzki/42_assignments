/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   contains_only_whitespaces.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:34:59 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/07 21:45:24 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	contains_only_whitespaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' '
			&& line[i] != '\t'
			&& line[i] != '\n'
			&& line[i] != '\r'
			&& line[i] != '\v')
			return (NO);
		i++;
	}
	return (YES);
}
