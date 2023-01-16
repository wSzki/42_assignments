/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 15:43:08 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 14:44:53 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (YES);
	return (NO);
}

int	is_alnum(char c)
{
	if (is_alpha(c) == YES || (c >= '0' && c <= '9'))
		return (YES);
	return (NO);
}

static int	is_valid_export_argument(char *str)
{
	int	i;

	i = -1;
	if (!is_alpha(str[++i]))
		return (NO);
	while (str[++i])
	{
		if (!is_alnum(str[i]))
		{
			if (str[i] == '=')
				return (YES);
			else
				return (NO);
		}
	}
	return (NO);
}

int	export(t_global *g, char **cmd_tab)
{
	int	i;

	i = 0;
	if (!cmd_tab)
		error_management("", errno);
	if (ft_strcmp(cmd_tab[0], "export") == 0)
	{
		while (cmd_tab[++i])
		{
			if (is_valid_export_argument(cmd_tab[i]) == YES)
			{
				add_or_replace_env_variable(g, cmd_tab[i]);
			}
			else
			{
				write(2, "minishell : export: `", 22);
				write(2, cmd_tab[i], ft_strlen(cmd_tab[i]));
				write(2, "': not a valid identifier\n", 27);
				g->last_exit = 1;
			}
		}
		return (IS_BUILTIN);
	}
	return (IS_NOT_BUILTIN);
}
