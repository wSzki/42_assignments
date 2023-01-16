/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 15:34:09 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:01:44 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	check_status(int *og, int status, int *fd)
{
	if (status == 0)
	{
		close(fd[1]);
		dup2(og[0], STDIN_FILENO);
		dup2(og[1], STDOUT_FILENO);
		dup2(fd[0], STDIN_FILENO);
		return (OK);
	}
	else
		return (ERROR);
}

static int	backup_fd(int *og, int *original_io)
{
	og[0] = dup(0);
	og[1] = dup(1);
	dup2(original_io[0], STDIN_FILENO);
	dup2(original_io[1], STDOUT_FILENO);
	return (0);
}

int	heredoc(char **op, int *i, int *fd, int *original_io)
{
	int		og[2];
	pid_t	pid;
	int		status;

	status = backup_fd(og, original_io);
	catch_empty_double_quotes(g_g->cmd_matrix, i);
	if (is_last_heredoc(&op[*i]) == NO)
	{
		if (readline_and_send_to_void(g_g->cmd_matrix, i) == ERROR)
			return (ERROR);
	}
	else
	{
		pid = fork();
		if (pid == 0)
			sub_heredoc(fd, g_g->cmd_matrix, i);
		signal(SIGINT, disable_main_signal_heredoc);
		wait(&status);
		manage_main_signal(g_g);
		return (check_status(og, status, fd));
	}
	dup2(og[0], STDIN_FILENO);
	dup2(og[1], STDOUT_FILENO);
	return (OK);
}
