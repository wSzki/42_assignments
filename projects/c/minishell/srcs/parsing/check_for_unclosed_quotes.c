/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_unclosed_quotes.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 15:54:23 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/25 14:39:09 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	toggle_quote_state(int *quote_state)
{
	if (*quote_state == OPEN)
		*quote_state = CLOSED;
	else if (*quote_state == CLOSED)
		*quote_state = OPEN;
}

static int	are_quotes_closed(char *str)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;

	i = -1;
	single_quote_state = CLOSED;
	double_quote_state = CLOSED;
	while (str[++i])
	{
		if (str[i] == SINGLE_QUOTE && double_quote_state == CLOSED)
			toggle_quote_state(&single_quote_state);
		else if (str[i] == DOUBLE_QUOTE && single_quote_state == CLOSED)
			toggle_quote_state(&double_quote_state);
	}
	if (single_quote_state == OPEN || double_quote_state == OPEN)
		return (NO);
	return (YES);
}

int	check_for_unclosed_quotes(char **tab)
{
	int	i;

	i = -1;
	while (tab[++i])
	{
		if (are_quotes_closed(tab[i]) == NO)
		{
			error_management("quotes unclosed\n", NO_EXIT);
			return (STOP);
		}
	}
	return (CONTINUE);
}
