/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 15:02:13 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/12 00:51:00 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sub_readline_and_send_to_void(char *line, char ***cmd, int *i)
{
	signal(SIGINT, heredoc_signal);
	line = readline("> ");
	if (line != NULL)
	{
		while (line != NULL && ft_strcmp(line, cmd[*i + 1][0]) != 0)
		{
			free(line);
			line = readline("> ");
		}
	}
	if (line == NULL)
		ft_putstr_fd("minishell: warning:\
here-document delimited by end-of-file (wanted `EOF')\n", 2);
	free(line);
	exit(0);
}

void	catch_empty_double_quotes(char ***cmd, int *i)
{
	if (ft_strcmp(cmd[*i + 1][0], "\"\"") == 0)
	{
		free(cmd[*i + 1][0]);
		cmd[*i + 1][0] = extract_string("", FULL_LENGTH);
	}
}

int	is_last_heredoc(char **op)
{
	int	i;

	i = 0;
	while (op[++i])
		if (ft_strcmp("<<", op[i]) == 0)
			return (NO);
	return (YES);
}

int	readline_and_send_to_void(char ***cmd, int *i)
{
	int		status;
	pid_t	pid;
	char	*line;

	line = NULL;
	status = 0;
	pid = fork();
	if (pid == 0)
		sub_readline_and_send_to_void(line, cmd, i);
	signal(SIGINT, disable_main_signal_heredoc);
	wait(&status);
	manage_main_signal(g_g);
	if (status == 0)
		return (OK);
	return (ERROR);
}

void	sub_heredoc(int *fd, char ***cmd, int *i)
{
	char	*line;

	line = NULL;
	signal(SIGINT, heredoc_signal);
	line = readline("> ");
	if (line != NULL)
	{
		while (line != NULL && ft_strcmp(line, cmd[*i + 1][0]) != 0)
		{
			write(fd[1], line, ft_strlen(line));
			write(fd[1], "\n", 1);
			free(line);
			line = readline("> ");
		}
	}
	if (line == NULL)
		ft_putstr_fd("minishell: warning: \
here-document delimited by end-of-file (wanted `EOF')\n", 2);
	exit(0);
}
