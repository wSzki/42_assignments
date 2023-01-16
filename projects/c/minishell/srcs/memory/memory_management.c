/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_management.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:23:22 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/01 15:14:31 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <readline/readline.h>

t_global	*init_cmd_data(t_global *g)
{
	g->sequence_tab = NULL;
	g->operator_tab = NULL;
	g->cmd_matrix = NULL;
	g->line = NULL;
	g->pid = 0;
	return (g);
}

void	double_free(void **tab)
{
	int	i;

	i = -1;
	if (tab)
	{
		while (tab[++i])
			free(tab[i]);
		free(tab[i]);
	}
	free(tab);
	tab = NULL;
}

void	free_cmd_data(t_global *g)
{
	int	i;

	double_free((void **)g->sequence_tab);
	double_free((void **)g->operator_tab);
	g->sequence_tab = NULL;
	g->operator_tab = NULL;
	i = -1;
	if (g->cmd_matrix)
	{
		while (g->cmd_matrix[++i])
			double_free((void **)g->cmd_matrix[i]);
		free(g->cmd_matrix[i]);
	}
	free(g->cmd_matrix);
	free(g->line);
	g->cmd_matrix = NULL;
	g->line = NULL;
}

void	free_all(t_global *g)
{
	rl_clear_history();
	free_cmd_data(g);
	double_free((void **)g->env);
	free(g);
}
