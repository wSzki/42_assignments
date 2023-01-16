/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_main_signal.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/06 12:45:41 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 16:24:59 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	reprompt(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_g->last_exit = 130;
	}
}

static void	reprompt_no_mewline(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_g->last_exit = 130;
	}
}

void	manage_main_signal(t_global *g)
{
	signal(SIGQUIT, SIG_IGN);
	if (check_minishell_lvl(g) == '1')
		signal(SIGINT, reprompt);
	else
		signal(SIGINT, reprompt_no_mewline);
}
