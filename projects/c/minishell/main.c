/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:48:25 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:44:57 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//
#include "./includes/minishell.h"

t_global	*g_g;

int	execution_dispatcher(t_global *g, int *status)
{
	char	***cmd;
	int		nb_of_cmd;

	cmd = g->cmd_matrix;
	nb_of_cmd = matrixlen(cmd);
	if (nb_of_cmd == 1)
		return (execute_single_command(g, cmd, status));
	if (only_pipes(g->operator_tab))
		execute_pipeline(g, cmd, status);
	else
		execute_redirections(g, status);
	return (CONTINUE);
}

int	minishell(t_global *g, int *status)
{
	g = init_cmd_data(g);
	g->line = readline("\033[1;34mMinishell > \033[m");
	if (g->line == NULL)
		g->line = extract_string("exit", FULL_LENGTH);
	if (*(g->line) != '\0' && contains_only_whitespaces(g->line) == NO)
	{
		add_history(g->line);
		if (extract_tokens(g) == CONTINUE)
			if (execution_dispatcher(g, status) == STOP)
				return (STOP);
	}
	free_cmd_data(g);
	return (CONTINUE);
}

int	main(int ac, char **av, char **env)
{
	int	return_value;
	int	status;

	(void)ac;
	status = 0;
	return_value = 0;
	g_g = malloc(sizeof(*g_g));
	if (!(g_g))
		error_management("", errno);
	g_g = init_cmd_data(g_g);
	init_env(g_g, av[0], env);
	g_g->last_exit = 0;
	while (1)
	{
		manage_main_signal(g_g);
		if (minishell(g_g, &status) == STOP)
			break ;
	}
	if (status)
		return_value = status;
	double_free((void **)g_g->env);
	g_g->env = NULL;
	free(g_g);
	return (return_value);
}
