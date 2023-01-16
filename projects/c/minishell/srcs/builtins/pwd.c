/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 22:21:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 14:45:54 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	catch_pwd_error(t_global *g, char **cmd_tab)
{
	if (cmd_tab[1] == NULL)
		return (0);
	ft_putstr_fd("minishell: pwd: ", 1);
	write(1, &cmd_tab[1][0], 1);
	write(1, &cmd_tab[1][1], 1);
	ft_putstr_fd(": invalid option\n", 1);
	ft_putstr_fd("pwd: usage: pwd [NO ARGUMENTS]\n", 1);
	g->last_exit = 2;
	return (1);
}

static void	print_cwd(t_global *g)
{
	char	*cwd;
	char	*tmp;

	tmp = custom_getenv("PWD", g->env);
	if (*tmp != '\0')
		cwd = getcwd(0, 0);
	else
		cwd = extract_string("", FULL_LENGTH);
	ft_putstr_fd(cwd, 1);
	write(1, "\n", 1);
	free(cwd);
	free(tmp);
	cwd = NULL;
}

int	pwd(t_global *g, char **cmd_tab)
{
	if (!cmd_tab)
		return (ERROR);
	if (ft_strcmp(cmd_tab[0], "pwd") == 0)
	{
		if (catch_pwd_error(g, cmd_tab) == NO_ERROR_FOUND)
			print_cwd(g);
		return (IS_BUILTIN);
	}
	return (IS_NOT_BUILTIN);
}
