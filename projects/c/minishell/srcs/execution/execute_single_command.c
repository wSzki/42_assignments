/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_single_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 18:02:02 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 14:40:22 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <stdlib.h>

int	execute_single_command(t_global *g, char ***cmd, int *status)
{
	if (catch_exit(g, cmd[0], status))
		return (STOP);
	if (is_builtin(cmd[0]))
		execute_builtin(g, cmd[0]);
	else
	{
		g->pid = fork();
		if (g->pid == 0)
			execute_bin(g, cmd[0]);
		else
		{
			manage_sub_signal(g);
			waitpid(g->pid, status, 0);
			if (WIFEXITED(*status))
				g->last_exit = WEXITSTATUS(*status);
		}
	}
	free_cmd_data(g);
	return (CONTINUE);
}
