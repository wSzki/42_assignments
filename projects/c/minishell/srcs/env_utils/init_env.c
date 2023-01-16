/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:41:38 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/21 17:14:27 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	key_found(t_global *g, char *key)
{
	int	i;
	int	len;

	i = -1;
	len = ft_strlen(key);
	while (g->env[++i])
	{
		if (ft_strncmp(key, g->env[i], len) == 0)
			return (YES);
	}
	return (NO);
}

static char	**duplicate_env(char **env)
{
	char	**env_tab;
	int		i;

	i = 0;
	while (env[i])
		i++;
	env_tab = malloc(sizeof(char **) * (i + 1));
	if (!env_tab)
		error_management("", errno);
	env_tab[i] = NULL;
	i = -1;
	while (env[++i])
		env_tab[i] = extract_string(env[i], FULL_LENGTH);
	return (env_tab);
}

void	init_env(t_global *g, char *minishell_path, char **env)
{
	char	*buffer;

	g->env = duplicate_env(env);
	buffer = ft_strjoin("SHELL=", minishell_path);
	add_or_replace_env_variable(g, buffer);
	if (key_found(g, "_MINISHELL_LVL") == NO)
		add_or_replace_env_variable(g, "_MINISHELL_LVL=1");
	else
		increment_env_variable(g, "_MINISHELL_LVL=");
	increment_env_variable(g, "SHLVL=");
	free(buffer);
}
