/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_at_operators.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/13 19:22:15 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/04 15:04:32 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static int	operator_type(char *str)
{
	int		i;
	char	*operators;

	i = 0;
	operators = "|><";
	while (operators[i])
	{
		if (operators[i] == str[0])
		{
			if (str[0] == '<' || str[0] == '>')
				if (str[1] == str[0])
					return (2);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	toggle_quote_state(int *quote_state)
{
	if (*quote_state == OPEN)
		*quote_state = CLOSED;
	else if (*quote_state == CLOSED)
		*quote_state = OPEN;
}

static int	find_index_of_next_operator(char *str)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;

	i = 0;
	single_quote_state = CLOSED;
	double_quote_state = CLOSED;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE && double_quote_state == CLOSED)
			toggle_quote_state(&single_quote_state);
		else if (str[i] == DOUBLE_QUOTE && single_quote_state == CLOSED)
			toggle_quote_state(&double_quote_state);
		else if (single_quote_state == CLOSED && double_quote_state == CLOSED)
			if (operator_type(&str[i]))
				return (i);
		i++;
	}
	return (NO_OPERATOR_FOUND);
}

static int	count_slots(char *cmd_str)
{
	int	operator_count;
	int	next_operator_index;

	operator_count = 0;
	while (1)
	{
		next_operator_index = find_index_of_next_operator(cmd_str);
		if (next_operator_index == NO_OPERATOR_FOUND)
			return (operator_count * 2 + 1);
		if (operator_type(cmd_str))
			operator_count++;
		cmd_str += next_operator_index + operator_type(cmd_str);
	}
}

char	**split_at_operators(char *cmd_str)
{
	int		i;
	char	**cmd_tab;
	int		next_operator_index;

	i = 0;
	cmd_tab = malloc(sizeof(char **) * (count_slots(cmd_str) + 1));
	if (!(cmd_tab))
		error_management("", errno);
	cmd_tab[count_slots(cmd_str)] = NULL;
	while (1)
	{
		next_operator_index = find_index_of_next_operator(cmd_str);
		if (NO_OPERATOR_FOUND == next_operator_index)
		{
			cmd_tab[i] = extract_string(cmd_str, FULL_LENGTH);
			return (cmd_tab);
		}
		cmd_tab[i++] = extract_string(cmd_str, next_operator_index);
		cmd_str = cmd_str + next_operator_index;
		cmd_tab[i++] = extract_string(cmd_str, operator_type(cmd_str));
		cmd_str = cmd_str + operator_type(cmd_str);
	}
}
