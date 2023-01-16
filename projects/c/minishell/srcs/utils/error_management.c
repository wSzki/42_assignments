/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_management.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adlancel <adlancel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/08 18:14:46 by adlancel          #+#    #+#             */
/*   Updated: 2021/11/05 16:23:42 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	sub_error_management(char *cmd, int exitcode)
{
	ft_putstr_fd("minishell: ", 2);
	if (exitcode < -1)
		ft_putstr_fd(cmd, 2);
	else
		perror(cmd);
	if (exitcode != NO_EXIT)
	{
		free_all(g_g);
		exit(exitcode);
	}
	else
		g_g->last_exit = 1;
}

void	error_management(char *cmd, int exitcode)
{
	if (exitcode > 126)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": command not found\n", 2);
		free_all(g_g);
		exit(exitcode);
	}
	else if (exitcode < 127)
	{
		sub_error_management(cmd, exitcode);
	}
	else
	{
		free_all(g_g);
		exit(errno);
	}
}

void	error_management_cd(char *cmd, int error_type)
{
	ft_putstr_fd("minishell : cd: ", 2);
	if (error_type == TOO_MANY_ARGUMENTS)
		ft_putstr_fd(": too many arguments\n", 2);
	else if (error_type == NO_SUCH)
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		g_g->last_exit = 1;
		return ;
	}
	else if (error_type == UNSET)
		ft_putstr_fd(" HOME not set\n", 2);
	g_g->last_exit = 1;
}
