/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 23:53:09 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:24:39 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	ft_is_num(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
		if (str[i] < '0' || str[i] > '9')
			return (1);
	return (0);
}

int	catch_exit(t_global *g, char **cmd_tab, int *status)
{
	if (ft_strcmp(cmd_tab[0], "exit") == 0)
	{
		ft_putstr_fd("exit\n", 1);
		if (cmd_tab[1] && !ft_is_num(cmd_tab[1]) && !cmd_tab[2])
			*status = ft_atoi(cmd_tab[1]);
		else
			status = 0;
		free_cmd_data(g);
		return (YES);
	}
	return (0);
}
