/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/15 20:43:58 by wszurkow          #+#    #+#             */
/*   Updated: 2021/11/05 15:08:24 by adlancel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

static void	toggle_quote_state(int *quote_state, int *quote_count)
{
	if (*quote_state == OPEN)
		*quote_state = CLOSED;
	else if (*quote_state == CLOSED)
		*quote_state = OPEN;
	*quote_count = *quote_count + 1;
}

static int	count_trimmable_quotes(char *str)
{
	int	i;
	int	single_quote_state;
	int	double_quote_state;
	int	quote_count;

	i = -1;
	quote_count = 0;
	single_quote_state = CLOSED;
	double_quote_state = CLOSED;
	while (str[++i])
	{
		if (str[i] == SINGLE_QUOTE && double_quote_state == CLOSED)
			toggle_quote_state(&single_quote_state, &quote_count);
		else if (str[i] == DOUBLE_QUOTE && single_quote_state == CLOSED)
			toggle_quote_state(&double_quote_state, &quote_count);
	}
	return (quote_count);
}

static char	*copy_without_trimmmable_quotes(char *str, char *new_str)
{
	int	i;
	int	j;
	int	single_quote_state;
	int	double_quote_state;
	int	quote_count;

	j = -1;
	i = -1;
	single_quote_state = CLOSED;
	double_quote_state = CLOSED;
	while (str[++i])
	{
		if (str[i] == SINGLE_QUOTE && double_quote_state == CLOSED)
			toggle_quote_state(&single_quote_state, &quote_count);
		else if (str[i] == DOUBLE_QUOTE && single_quote_state == CLOSED)
			toggle_quote_state(&double_quote_state, &quote_count);
		else
			new_str[++j] = str[i];
	}
	return (new_str);
}

static char	*sub_trim_quotes(char *str)
{
	int		trimmable_quote_count;
	int		len;
	char	*new_str;

	trimmable_quote_count = count_trimmable_quotes(str);
	len = ft_strlen(str) - trimmable_quote_count;
	new_str = malloc(sizeof(*new_str) * (len + 1));
	if (!(new_str))
		error_management("", errno);
	new_str[len] = '\0';
	new_str = copy_without_trimmmable_quotes(str, new_str);
	free(str);
	return (new_str);
}

char	***trim_quotes(t_global *g, char ***cmd_tab)
{
	int	i;
	int	j;
	int	flag;

	i = 0;
	while (cmd_tab[i])
	{
		j = -1;
		while (cmd_tab[i][++j])
		{
			flag = 1;
			if (i > 0)
				if (ft_strcmp(g->operator_tab[i - 1], "<<") == 0)
					if ((ft_strcmp(cmd_tab[i][0], "\"\"")) == 0)
						flag = 0;
			if (flag)
				cmd_tab[i][j] = sub_trim_quotes(cmd_tab[i][j]);
		}
		i++;
	}
	return (cmd_tab);
}
