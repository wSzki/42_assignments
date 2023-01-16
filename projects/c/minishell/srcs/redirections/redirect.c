/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 10:51:54 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:02:16 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	catch_file_not_found(t_global *g, int i, int file)
{
	i++;
	if (file == ERROR)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(g->cmd_matrix[i][0], 2);
		ft_putstr_fd(": ", 2);
		perror("");
		g->last_exit = 1;
		return (ERROR);
	}
	else
		return (OK);
}

static int	open_or_heredoc(int *file, int *i, int *fd, int *original_io)
{
	char	**op;
	char	***cmd;
	mode_t	mode;

	op = g_g->operator_tab;
	cmd = g_g->cmd_matrix;
	mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	if (ft_strcmp("<", op[*i]) == 0)
		*file = open(cmd[*i + 1][0], O_RDONLY);
	if (ft_strcmp(">", op[*i]) == 0)
		*file = open(cmd[*i + 1][0], O_TRUNC | O_RDWR | O_CREAT, mode);
	if (ft_strcmp(">>", op[*i]) == 0)
		*file = open(cmd[*i + 1][0], O_APPEND | O_RDWR | O_CREAT, mode);
	if (ft_strcmp("<<", op[*i]) == 0)
		if (heredoc(op, i, fd, original_io) == ERROR)
			return (ERROR);
	if (catch_file_not_found(g_g, *i, *file) == ERROR)
	{
		if (ft_strcmp("<", op[*i]) == 0)
			return (ERROR);
	}
	return (OK);
}

static int	perform_io_dup2(int file, char **op, int i)
{
	int	status;

	status = 0;
	if (ft_strcmp("<", op[i]) == 0)
		status = dup2(file, STDIN_FILENO);
	if (ft_strcmp(">", op[i]) == 0)
		status = dup2(file, STDOUT_FILENO);
	if (ft_strcmp(">>", op[i]) == 0)
		status = dup2(file, STDOUT_FILENO);
	return (status);
}

static char	**mv_args_to_origin(t_global *g, char **old_cmd_seq, char *file)
{
	int		i;
	int		len;
	char	**new_cmd_seq;

	(void)g;
	len = -1;
	while (old_cmd_seq[++len])
		;
	new_cmd_seq = malloc(sizeof(char *) * (len + 2));
	if (!(new_cmd_seq))
		error_management("", errno);
	new_cmd_seq[len + 1] = NULL;
	i = -1;
	if (old_cmd_seq)
	{
		while (old_cmd_seq[++i])
		{
			new_cmd_seq[i] = extract_string(old_cmd_seq[i], FULL_LENGTH);
			free(old_cmd_seq[i]);
		}
	}
	free(old_cmd_seq);
	new_cmd_seq[i] = extract_string(file, FULL_LENGTH);
	return (new_cmd_seq);
}

int	redirect(t_global *g, int *i, int *fd, int *original_io)
{
	int		j;
	int		file;
	int		origin;
	char	**op;
	char	***cmd;

	file = 0;
	cmd = g->cmd_matrix;
	origin = *i;
	op = g->operator_tab;
	while (op[*i] && is_redirection(op[*i]))
	{
		if (catch_unexpected_token(g, i) == ERROR)
			return (ERROR);
		if (open_or_heredoc(&file, i, fd, original_io) == ERROR)
			return (ERROR);
		if (perform_io_dup2(file, op, *i) == ERROR)
			error_management("", errno);
		j = 0;
		while (cmd[*i + 1][++j])
			cmd[origin] = mv_args_to_origin(g, cmd[origin], cmd[*i + 1][j]);
		*i += 1;
	}
	return (OK);
}
