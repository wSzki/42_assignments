/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 16:27:34 by wszurkow          #+#    #+#             */
/*   Updated: 2021/12/12 20:04:38 by jbesnier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "hotrace.h"

static int	is_first_line_empty(t_global *g, char **line)
{
	int	r;

	r = get_next_line(line);
	if (r < 1)
	{
		g->status = errno;
		return (YES);
	}
	if (r == 0)
	{
		g->status = ERR_PARSING;
		return (YES);
	}
	if (**line == '\0')
	{
		g->status = ERR_PARSING;
		free(*line);
		*line = NULL;
		return (YES);
	}
	g->haystack[(g->nb_hay)++] = ft_strdup(g, *line);
	free(*line);
	*line = NULL;
	return (NO);
}

void	parse_input_file(t_global *g, char **line)
{
	int	empty_line_found;

	*line = NULL;
	empty_line_found = NO;
	if (is_first_line_empty(g, line) == YES)
		return ;
	while (get_next_line(line) > 0)
	{
		if (**line == '\0')
		{
			free(*line);
			*line = NULL;
			break ;
		}
		if (empty_line_found == NO)
		{
			g->haystack[(g->nb_hay)++] = ft_strdup(g, *line);
			if (g->haystack[(g->nb_hay - 1)] == NULL)
				return ;
		}
		free(*line);
		*line = NULL;
	}
	if (g->nb_hay % 2 != 0)
		g->status = ERR_PARSING;
}
