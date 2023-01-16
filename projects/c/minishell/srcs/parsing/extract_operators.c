/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_operators.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:23:43 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/21 17:20:44 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	**extract_operators(char **tab)
{
	int		i;
	int		j;
	char	**operator_tab;

	i = -1;
	j = 0;
	while (tab[++i])
		if (i % 2 == 1)
			j++;
	operator_tab = malloc(sizeof(char **) * (j + 1));
	if (!(operator_tab))
		error_management("", errno);
	operator_tab[j] = NULL;
	i = -1;
	j = 0;
	while (tab[++i])
	{
		if (i % 2 == 1)
		{
			operator_tab[j] = extract_string(tab[i], FULL_LENGTH);
			j++;
		}
	}
	return (operator_tab);
}
