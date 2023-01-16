/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 19:27:50 by wszurkow          #+#    #+#             */
/*   Updated: 2021/10/21 17:20:27 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NO_WHITESPACE_FOUND -1

static void	toggle_quote_state(int *quote_state)
{
	if (*quote_state == OPEN)
		*quote_state = CLOSED;
	else if (*quote_state == CLOSED)
		*quote_state = OPEN;
}

static int	find_index_of_next_whitespace(char *str)
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
			if (is_it_whitespace(&str[i]) == YES)
				return (i);
		i++;
	}
	return (NO_WHITESPACE_FOUND);
}

static int	count_slots(char *cmd_str)
{
	int	whitespace_count;
	int	next_whitespace_index;

	whitespace_count = 0;
	while (1)
	{
		next_whitespace_index = find_index_of_next_whitespace(cmd_str);
		if (next_whitespace_index == NO_WHITESPACE_FOUND)
			return (whitespace_count + 1);
		whitespace_count++;
		cmd_str += next_whitespace_index;
		while (*cmd_str && is_it_whitespace(cmd_str) == YES)
			cmd_str++;
	}
}

char	**split_command_and_arguments(char *cmd_str)
{
	int		i;
	char	**cmd_tab;
	int		next_whitespace_index;

	i = 0;
	cmd_tab = malloc(sizeof(char *) * (count_slots(cmd_str) + 1));
	if (!(cmd_tab))
		error_management("", errno);
	cmd_tab[count_slots(cmd_str)] = NULL;
	while (1)
	{
		next_whitespace_index = find_index_of_next_whitespace(cmd_str);
		if (NO_WHITESPACE_FOUND == next_whitespace_index)
		{
			cmd_tab[i] = extract_string(cmd_str, FULL_LENGTH);
			return (cmd_tab);
		}
		cmd_tab[i++] = extract_string(cmd_str, next_whitespace_index);
		cmd_str += next_whitespace_index;
		while (*cmd_str && is_it_whitespace(cmd_str) == YES)
			cmd_str++;
	}
	return (NULL);
}

char	***exctract_commands(char **tab)
{
	int		i;
	int		j;
	char	***cmd_matrix;

	i = -1;
	j = 0;
	while (tab[++i])
		if (i % 2 == 0)
			j++;
	cmd_matrix = malloc(sizeof(char **) * (j + 1));
	if (!(cmd_matrix))
		error_management("", errno);
	cmd_matrix[j] = NULL;
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (i % 2 == 0)
		{
			cmd_matrix[j] = split_command_and_arguments(tab[i]);
			j++;
		}
		i++;
	}
	return (cmd_matrix);
}
