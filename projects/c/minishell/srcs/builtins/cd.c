/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 22:19:39 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 14:38:27 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static	void	cd_to_tilde(t_global *g)
{
	char	*path;
	char	*pwd_env;
	int		i;

	i = -1;
	while (g->env[++i])
		if (ft_strcmp(g->env[i], "HOME=") == 0)
			return ;
	path = custom_getenv("HOME", g->env);
	pwd_env = ft_strjoin("PWD=", path);
	add_or_replace_env_variable(g, pwd_env);
	if (-1 == chdir(path))
	{
		free(path);
		free(pwd_env);
		error_management_cd("", UNSET);
		g->last_exit = 1;
	}
	else
	{
		free(path);
		free(pwd_env);
	}
}

static void	cd_with_absolute_path(char **cmd_tab, t_global *g)
{
	char	*pwd_env;

	pwd_env = ft_strjoin("PWD=", cmd_tab[1]);
	add_or_replace_env_variable(g, pwd_env);
	if (-1 == chdir(cmd_tab[1]))
	{
		error_management_cd(cmd_tab[1], NO_SUCH);
		g->last_exit = 1;
	}
	free(pwd_env);
}

static void	cd_with_relative__path(char **cmd_tab, t_global *g)
{
	char	*pwd_env;
	char	*path;
	char	*tmp;

	tmp = custom_getenv("PWD", g->env);
	path = ft_strjoin("PWD=", tmp);
	pwd_env = ft_strjoin(path, cmd_tab[1]);
	add_or_replace_env_variable(g, pwd_env);
	free (path);
	free (tmp);
	free(pwd_env);
	if (-1 == chdir(cmd_tab[1]))
		error_management_cd(cmd_tab[1], NO_SUCH);
}

int	cd(t_global *g, char **cmd_tab)
{
	if (!cmd_tab)
		error_management("", errno);
	if (ft_strcmp(cmd_tab[0], "cd") == 0)
	{
		if (tablen(cmd_tab) == 2)
		{
			if (cmd_tab[1][0] == '/')
				cd_with_absolute_path(cmd_tab, g);
			else if (cmd_tab[1][0] == '~')
				cd_to_tilde(g);
			else
				cd_with_relative__path(cmd_tab, g);
		}
		else if (tablen(cmd_tab) > 2)
			error_management_cd("", TOO_MANY_ARGUMENTS);
		else if (tablen(cmd_tab) == 1)
			cd_to_tilde(g);
		return (1);
	}
	return (0);
}
