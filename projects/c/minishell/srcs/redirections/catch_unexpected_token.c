/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_unexpected_token.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 13:24:46 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 14:35:12 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	catch_unexpected_token(t_global *g, int *head)
{
	char	*str;
	int		i;

	i = *head + 1;
	str = "minishell: syntax error near unexpected token `newline'\n";
	if (g->cmd_matrix[i][0][0] == '\0')
	{
		if (g->operator_tab[i] == NULL)
			ft_putstr_fd(str, 2);
		else
		{
			ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
			ft_putstr_fd(g->operator_tab[i], 2);
			ft_putstr_fd("'\n", 2);
		}
		g->last_exit = 2;
		return (ERROR);
	}
	else
		return (OK);
}
