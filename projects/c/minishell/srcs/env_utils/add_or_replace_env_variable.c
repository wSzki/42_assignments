/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_or_replace_env_variable.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 18:46:28 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/12 13:53:19 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*extract_key(char *key_and_value)
{
	int		i;
	char	*key;

	i = -1;
	while (key_and_value[++i])
	{
		if (key_and_value[i] == '=')
		{
			if (only_whitespaces(&key_and_value[i + 1]))
				key_and_value[i + 1] = '\0';
			break ;
		}
	}
	key = extract_string(key_and_value, i);
	return (key);
}

static void	sub_add_or_replace_env_variable(t_global *g, char *key_and_value)
{
	int		i;
	char	**env_copy;

	i = 0;
	while (g->env[i])
		i++;
	env_copy = malloc(sizeof(*env_copy) * (i + 2));
	if (!(env_copy))
		error_management("", errno);
	env_copy[i + 1] = NULL;
	i = 0;
	while (g->env[i])
	{
		env_copy[i] = extract_string(g->env[i], FULL_LENGTH);
		i++;
	}
	env_copy[i] = extract_string(key_and_value, FULL_LENGTH);
	i = -1;
	double_free((void **)g->env);
	g->env = env_copy;
}

void	add_or_replace_env_variable(t_global *g, char *key_and_value)
{
	int		i;
	int		len;
	char	*key;
	int		key_found;

	i = -1;
	key = extract_key(key_and_value);
	key_found = NO;
	len = ft_strlen(key);
	while (g->env[++i])
	{
		if (ft_strncmp(key, g->env[i], len) == 0)
		{
			free(g->env[i]);
			g->env[i] = extract_string(key_and_value, FULL_LENGTH);
			key_found = YES;
		}
	}
	if (key_found == NO)
		sub_add_or_replace_env_variable(g, key_and_value);
	free(key);
}
