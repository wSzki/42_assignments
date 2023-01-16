/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 16:51:04 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/19 15:38:13 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	unset(t_global *g, char **cmd_tab)
{
	int	i;
	int	j;

	i = 0;
	if (!cmd_tab || !(g->env))
		return (ERROR);
	if (ft_strcmp(cmd_tab[0], "unset"))
		return (IS_NOT_BUILTIN);
	while (cmd_tab[++i])
	{
		j = -1;
		while (g->env[++j])
		{
			if (!ft_strncmp(g->env[j], cmd_tab[i], ft_strlen(cmd_tab[i])))
			{
				if (g->env[j][ft_strlen(cmd_tab[i])] == '=')
				{
					free(g->env[j]);
					g->env[j] = extract_string("", FULL_LENGTH);
				}
			}
		}
	}
	return (IS_BUILTIN);
}
