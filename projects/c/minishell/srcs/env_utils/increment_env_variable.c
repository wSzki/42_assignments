/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   increment_env_variable.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 22:30:03 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 12:25:19 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*increment_key_value(char *str)
{
	int		i;
	int		int_value;
	char	*char_value;

	i = 0;
	char_value = NULL;
	while (str[i])
	{
		if (str[i] == '=')
		{
			char_value = extract_string(&str[i + 1], FULL_LENGTH);
			break ;
		}
		i++;
	}
	int_value = ft_atoi(char_value);
	int_value++;
	free(char_value);
	char_value = ft_itoa(int_value);
	return (char_value);
}

void	increment_env_variable(t_global *g, char *key)
{
	int		i;
	int		len;
	char	*key_value;

	i = 0;
	len = ft_strlen(key);
	while (g->env[++i])
	{
		if (ft_strncmp(key, g->env[i], len) == 0)
		{
			key_value = increment_key_value(g->env[i]);
			free(g->env[i]);
			g->env[i] = ft_strjoin(key, key_value);
			free(key_value);
		}
	}
}
