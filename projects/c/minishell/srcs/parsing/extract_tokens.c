/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 14:36:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/03 16:38:24 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NO_EXPANSION_FOUND -1
#define PIPE_ERROR "syntax error near unexpected token `|'\n"

static int	check_empty_pipes(t_global *g, char ***cmd, char **op)
{
	int		i;

	(void)g;
	i = -1;
	if (matrixlen(cmd) > 1)
	{
		while (op[++i])
		{
			if ((ft_strcmp("|", op[i]) == 0) && (cmd[i][0][0] == '\0'))
			{
				error_management(PIPE_ERROR, NO_EXIT);
				return (STOP);
			}
		}
		if ((ft_strcmp("|", op[i - 1])) == 0 && (cmd[i][0][0] == '\0'))
		{
			error_management(PIPE_ERROR, NO_EXIT);
			return (STOP);
		}
	}
	return (CONTINUE);
}

static int	extract_sequences_and_operators(char *line, char ***sequence_tab)
{
	*sequence_tab = split_at_operators(line);
	*sequence_tab = trim_whitespaces(*sequence_tab);
	return (check_for_unclosed_quotes(*sequence_tab));
}

int	extract_tokens(t_global *g)
{
	int	ret;

	ret = extract_sequences_and_operators(g->line, &(g->sequence_tab));
	if (ret == STOP)
		return (STOP);
	g->sequence_tab = expand_env_variables(g, g->sequence_tab);
	g->cmd_matrix = exctract_commands(g->sequence_tab);
	g->operator_tab = extract_operators(g->sequence_tab);
	g->cmd_matrix = trim_quotes(g, g->cmd_matrix);
	ret = check_empty_pipes(g, g->cmd_matrix, g->operator_tab);
	if (ret == STOP)
		return (STOP);
	return (CONTINUE);
}
