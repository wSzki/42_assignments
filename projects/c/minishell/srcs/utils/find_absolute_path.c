/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_absolute_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 17:44:11 by adlancel          #+#    #+#             */
/*   Updated: 2021/10/20 16:34:24 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static char	*sub_path(char *valid_path, char *tmp_path, char **all_paths)
{
	int	i;

	i = -1;
	free(tmp_path);
	while (all_paths[++i])
		free(all_paths[i]);
	free(all_paths);
	return (valid_path);
}

char	*find_absolute_path(t_global *g, char *cmd)
{
	char	**all_paths;
	char	*tmp_path;
	char	*valid_path;
	int		i;

	i = -1;
	tmp_path = custom_getenv("PATH", g->env);
	all_paths = ft_split(tmp_path, ':');
	free(tmp_path);
	while (all_paths[++i])
	{
		tmp_path = ft_strjoin(all_paths[i], "/");
		valid_path = ft_strjoin(tmp_path, cmd);
		if (access(valid_path, F_OK) != -1)
			return (sub_path(valid_path, tmp_path, all_paths));
		free(tmp_path);
		tmp_path = NULL;
		free(valid_path);
		valid_path = NULL;
	}
	i = -1;
	while (all_paths[++i])
		free(all_paths[i]);
	free(all_paths);
	return (extract_string("", 1));
}
