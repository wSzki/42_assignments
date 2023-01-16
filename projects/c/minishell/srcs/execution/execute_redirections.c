/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirections.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:58:30 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/12 00:58:46 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	no_output_redir(t_global *g, int *i)
{
	int	j;

	j = *i;
	while (j < 0 && *(g->operator_tab[j - 1]) != '|')
	{
		if (*g->operator_tab[j - 1] == '>')
			return (YES);
		j--;
	}
	return (NO);
}

static void	child_redirected_pipeline(int origin, int *i, int *fd, int *fd_in)
{
	char	***cmd;
	int		status;

	cmd = g_g->cmd_matrix;
	manage_sub_signal(g_g);
	if (ft_strcmp("exit", cmd[origin][0]) == 0)
		exit(0);
	dup2(*fd_in, STDIN_FILENO);
	if (cmd[*i + 1] != NULL && *g_g->operator_tab[*i] == '|')
		if (no_output_redir(g_g, i) == NO)
			dup2(fd[1], 1);
	close(fd[0]);
	if (is_builtin(cmd[origin]) == YES)
	{
		execute_builtin(g_g, cmd[origin]);
		status = g_g->last_exit;
		free_all(g_g);
		exit(status);
	}
	execute_bin(g_g, cmd[origin]);
}

static int	redirect_and_pipe_and_execute(t_global *g, int *i, int *fd_in)
{
	pid_t	pid;
	int		fd[2];
	int		original_io[2];
	int		origin;
	char	***cmd;

	cmd = g->cmd_matrix;
	origin = *i;
	if (pipe(fd) == ERROR)
		error_management("", errno);
	original_io[0] = dup(STDIN_FILENO);
	original_io[1] = dup(STDOUT_FILENO);
	if (redirect(g, i, fd, original_io) == ERROR)
		return (restore_io_error(original_io));
	if (ft_strcmp("", cmd[origin][0]) == 0 && cmd[origin][1] == NULL)
		return (restore_io_continue(original_io, i));
	pid = fork();
	if (pid == ERROR)
		error_management("", errno);
	manage_sub_signal(g);
	if (pid == 0)
		child_redirected_pipeline(origin, i, fd, fd_in);
	else
		restore_io(i, fd, fd_in, original_io);
	return (CONTINUE);
}

void	execute_redirections(t_global *g, int *status)
{
	int		i;
	int		fd_in;
	int		fd_to_close;
	char	***cmd_sequence;

	i = 0;
	fd_in = 0;
	cmd_sequence = g->cmd_matrix;
	while (cmd_sequence[i])
	{
		if (redirect_and_pipe_and_execute(g, &i, &fd_in) == ERROR)
			break ;
		if (cmd_sequence[i] == NULL)
			wait(status);
	}
	fd_to_close = 2;
	while (++fd_to_close <= fd_in)
		close(fd_to_close);
	while (wait(NULL) > 0)
		;
}
