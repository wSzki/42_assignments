/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_minishell_lvl.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:48:11 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/19 16:22:42 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	check_minishell_lvl(t_global *g)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen("_MINISHELL_LVL=");
	while (g->env[i])
	{
		if (ft_strncmp("_MINISHELL_LVL=", g->env[i], len) == 0)
		{
			return (g->env[i][len]);
		}
		i++;
	}
	return (0);
}
