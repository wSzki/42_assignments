/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_signal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:41:22 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 15:59:56 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	heredoc_signal(int sig)
{
	if (sig == SIGINT)
		exit(1);
}

void	disable_main_signal_heredoc(int sig)
{
	if (sig == SIGINT)
	{
		if (check_minishell_lvl(g_g) == '1')
			write(1, "^C\n", 3);
		else
		{
			write(1, "^C", 2);
		}
		return ;
	}
}
