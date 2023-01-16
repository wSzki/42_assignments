/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_env_variables.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 17:36:53 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 15:18:35 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

#define NO_EXPANSION_FOUND -1

static void	toggle_quote_state(int *quote_state)
{
	if (*quote_state == OPEN)
		*quote_state = CLOSED;
	else if (*quote_state == CLOSED)
		*quote_state = OPEN;
}

static int	find_index_of_next_expansion(char *str)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;

	i = 0;
	single_quote_state = CLOSED;
	double_quote_state = CLOSED;
	while (str[i])
	{
		if (single_quote_state == CLOSED && double_quote_state == CLOSED)
			if (str[i] == '$' && (is_alphabet(str[i + 1]) || str[i + 1] == '?'))
				return (i);
		if (single_quote_state == CLOSED && double_quote_state == OPEN)
			if (str[i] == '$' && (is_alphabet(str[i + 1]) || str[i + 1] == '?'))
				return (i);
		if (str[i] == SINGLE_QUOTE && double_quote_state == CLOSED)
			toggle_quote_state(&single_quote_state);
		else if (str[i] == DOUBLE_QUOTE && single_quote_state == CLOSED)
			toggle_quote_state(&double_quote_state);
		i++;
	}
	return (NO_EXPANSION_FOUND);
}

char	*translate_expansion(t_global *g, char *str, int *head)
{
	int		i;
	char	*buffer_str;
	char	*ret_str;

	i = 0;
	if (str[1] == '?')
	{
		*head = *head + 2;
		ret_str = ft_itoa(g->last_exit);
		return (ret_str);
	}
	while (str[++i])
		if (is_alphabet(str[i]) == NO)
			break ;
	buffer_str = extract_string(&str[1], i - 1);
	*head = *head + i;
	ret_str = custom_getenv(buffer_str, g->env);
	free(buffer_str);
	if (ret_str[0] == '\0')
		return (ret_str);
	return (wrap_each_word_with_double_quotes(ret_str, -1, -1, -1));
}

static char	*sub_expand_env_variables(t_global *g, char *str)
{
	int		head;
	int		next_expansion_index;
	char	*expanded_str;
	char	*buffer_str;

	head = 0;
	expanded_str = extract_string("", 1);
	while (1)
	{
		next_expansion_index = find_index_of_next_expansion(&str[head]);
		buffer_str = extract_string(&str[head], next_expansion_index);
		expanded_str = ft_strjoin_and_free(expanded_str, buffer_str);
		buffer_str = NULL;
		if (NO_EXPANSION_FOUND == next_expansion_index)
			return (expanded_str);
		head += next_expansion_index;
		buffer_str = translate_expansion(g, &str[head], &head);
		expanded_str = ft_strjoin_and_free(expanded_str, buffer_str);
		buffer_str = NULL;
	}
}

char	**expand_env_variables(t_global *g, char **tab)
{
	int		i;
	char	*old_str;

	i = -1;
	while (tab[++i])
	{
		old_str = tab[i];
		tab[i] = sub_expand_env_variables(g, old_str);
		free(old_str);
	}
	return (tab);
}
