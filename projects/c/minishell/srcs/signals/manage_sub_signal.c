/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_sub_signal.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 13:14:17 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 15:57:40 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include <signal.h>

static void	only_newline(int sig)
{
	(void)sig;
	if (sig == SIGINT)
	{
		g_g->last_exit = 130;
		write(1, "\n", 1);
	}
}

static void	disable_signal(int sig)
{
	(void)sig;
	g_g->last_exit = 130;
}

void	manage_sub_signal(t_global *g)
{
	if (check_minishell_lvl(g) == '1')
		signal(SIGINT, only_newline);
	else
		signal(SIGINT, disable_signal);
}
