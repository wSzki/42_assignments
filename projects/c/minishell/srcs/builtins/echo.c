/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 17:53:49 by adlancel          #+#    #+#             */
/*   Updated: 2021/11/01 19:06:51 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	echo_with_nl(char **cmd_tab)
{
	int	i;

	i = 1;
	if (cmd_tab[i])
	{
		while (cmd_tab[i + 1] != NULL)
		{
			ft_putstr_fd(cmd_tab[i], 1);
			ft_putstr_fd(" ", 1);
			i++;
		}
		ft_putstr_fd(cmd_tab[i], 1);
	}
	ft_putstr_fd("\n", 1);
}

static int	check_n(char *cmd_tab)
{
	int	i;

	i = 0;
	while (cmd_tab[++i])
	{
		if (cmd_tab[i] != 'n')
			return (0);
	}
	return (1);
}

static void	echo_without_nl(char **cmd_tab, int i)
{
	if (cmd_tab[i])
	{
		while (cmd_tab[i])
		{
			ft_putstr_fd(cmd_tab[i], 1);
			if (cmd_tab[i + 1])
				ft_putstr_fd(" ", 1);
			i++;
		}
	}
}

int	echo(t_global *g, char **cmd_tab)
{
	int	i;

	i = 0;
	if (!cmd_tab)
		return (-1);
	if (!ft_strcmp(cmd_tab[0], "echo"))
	{
		g->last_exit = 0;
		if (cmd_tab[1])
		{
			while (cmd_tab[++i] && !ft_strncmp(cmd_tab[i], "-n", 2)
				&& check_n(cmd_tab[i]))
				;
			if (i > 1)
				echo_without_nl(cmd_tab, i);
			else
				echo_with_nl(cmd_tab);
			return (IS_BUILTIN);
		}
		echo_with_nl(cmd_tab);
		return (IS_BUILTIN);
	}
	return (IS_NOT_BUILTIN);
}
