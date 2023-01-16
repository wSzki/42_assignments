/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 19:25:41 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/01 17:58:00 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	execute_builtin(t_global *g, char **cmd_tab)
{
	int	len;
	int	is_builtin;

	len = tablen(cmd_tab);
	if (len > 1)
	{
		if (*(cmd_tab[0]) == '\0')
			cmd_tab++;
		len = tablen(cmd_tab);
		if (*cmd_tab[len - 1] == '\0')
		{
			free(cmd_tab[len]);
			free(cmd_tab[len - 1]);
			cmd_tab[len - 1] = NULL;
		}
	}
	is_builtin = 0;
	is_builtin += pwd(g, cmd_tab);
	is_builtin += echo(g, cmd_tab);
	is_builtin += cd(g, cmd_tab);
	is_builtin += export(g, cmd_tab);
	is_builtin += unset(g, cmd_tab);
	is_builtin += env(g, cmd_tab);
	return (is_builtin);
}
