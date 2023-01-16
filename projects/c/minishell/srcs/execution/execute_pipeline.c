/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 16:28:49 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:29:24 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	only_pipes(char **op)
{
	int	i;

	i = -1;
	while (op[++i])
		if (ft_strcmp(op[i], "|") != 0)
			return (NO);
	return (YES);
}

static void	sub_child_action(t_global *g, char **cmd, int status)
{
	execute_builtin(g, cmd);
	status = g->last_exit;
	free_all(g);
	exit(status);
}

static void	child_action(t_global *g, int *fd_in, int *fd, int i)
{
	char	***cmd;
	int		status;

	status = 0;
	cmd = g->cmd_matrix;
	manage_sub_signal(g);
	if (ft_strcmp("exit", cmd[i][0]) == 0)
	{
		if (cmd[i][1])
			exit(ft_atoi(cmd[i][1]));
		exit(0);
	}
	if (dup2(*fd_in, 0) == -1)
		error_management("", errno);
	if (cmd[i + 1] != NULL)
		if (dup2(fd[1], 1) == -1)
			error_management("", errno);
	close(fd[0]);
	if (is_builtin(cmd[i]) == YES)
		sub_child_action(g, cmd[i], status);
	execute_bin(g, cmd[i]);
}

static void	pipeline_subprocess(t_global *g, int i, int *fd_in)
{
	int	fd[2];

	if (pipe(fd) == -1)
		error_management("", errno);
	g->pid = fork();
	if (g->pid == -1)
		error_management("", errno);
	manage_sub_signal(g);
	if (g->pid == 0)
		child_action(g, fd_in, fd, i);
	else
	{
		close(fd[1]);
		*fd_in = fd[0];
	}
}

void	execute_pipeline(t_global *g, char ***cmd, int *status)
{
	int	i;
	int	fd_to_close;
	int	fd_in;

	i = -1;
	fd_in = 0;
	fd_to_close = 3;
	while (cmd[++i])
	{
		pipeline_subprocess(g, i, &fd_in);
		if (cmd[i + 1] == NULL)
		{
			waitpid(g->pid, status, 0);
			g->last_exit = WEXITSTATUS(*status);
		}
	}
	while (fd_to_close <= fd_in)
	{
		close(fd_to_close);
		fd_to_close++;
	}
	while (wait(NULL) > 0)
		;
}
