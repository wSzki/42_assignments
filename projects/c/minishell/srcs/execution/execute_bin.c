/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:02:33 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/11 22:22:23 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*parse_path(t_global *g, char **cmd_tab)
{
	char	*absolute_path;
	char	*tmp;

	absolute_path = NULL;
	if (cmd_tab[0])
	{
		if (ft_strncmp(cmd_tab[0], "./", 2) == 0)
		{
			tmp = getcwd(NULL, 0);
			absolute_path = ft_strjoin(tmp, &cmd_tab[0][1]);
			free(tmp);
		}
		else if (cmd_tab[0][0] == '/' )
			absolute_path = extract_string(cmd_tab[0], FULL_LENGTH);
		else
			absolute_path = find_absolute_path(g, cmd_tab[0]);
	}
	return (absolute_path);
}

static char	**sub_execute_bin(char **cmd_tab, int len)
{
	if (*(cmd_tab[0]) == '\0')
		cmd_tab++;
	len = tablen(cmd_tab);
	if (*cmd_tab[len - 1] == '\0')
	{
		free(cmd_tab[len]);
		free(cmd_tab[len - 1]);
		cmd_tab[len - 1] = NULL;
	}
	return (cmd_tab);
}

int	execute_bin(t_global *g, char **cmd_tab)
{
	int		len;
	char	*absolute_path;

	len = tablen(cmd_tab);
	absolute_path = NULL;
	if (len > 1)
		cmd_tab = sub_execute_bin(cmd_tab, len);
	absolute_path = parse_path(g, cmd_tab);
	if (absolute_path == NULL)
		error_management(cmd_tab[0], 126);
	else if (execve(absolute_path, cmd_tab, g->env) == -1)
	{
		free(absolute_path);
		error_management(cmd_tab[0], 127);
	}
	free(absolute_path);
	return (0);
}
