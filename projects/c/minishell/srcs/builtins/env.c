/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:01:24 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/21 17:10:24 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	env(t_global *g, char **cmd_tab)
{
	int	i;

	i = 0;
	if (!cmd_tab)
		error_management("", errno);
	if (ft_strcmp(cmd_tab[0], "env") == 0)
	{
		while (g->env[i])
		{
			if (g->env[i][0] != '\0')
			{
				ft_putstr_fd(g->env[i], 1);
				ft_putstr_fd("\n", 1);
			}
			i++;
		}
		return (IS_BUILTIN);
	}
	return (IS_NOT_BUILTIN);
}
