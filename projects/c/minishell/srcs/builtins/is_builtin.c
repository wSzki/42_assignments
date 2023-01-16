/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 18:59:21 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/19 15:33:21 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	is_builtin(char **cmd_tab)
{
	if (ft_strcmp("cd", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("echo", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("unset", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("env", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("pwd", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("echo", cmd_tab[0]) == 0)
		return (YES);
	if (ft_strcmp("export", cmd_tab[0]) == 0)
		return (YES);
	return (NO);
}
