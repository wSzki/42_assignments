/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub_parsing_fetch_data.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wszurkow <wszurkow@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 18:39:23 by wszurkow          #+#    #+#             */
/*   Updated: 2022/04/30 18:43:58 by wszurkow         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cub_parsing_free_split(char ***s, char **line)
{
	char	**split_line;

	split_line = *s;
	if (line)
	{
		free(*line);
		*line = NULL;
	}
	if (split_line)
	{
		while (*split_line)
		{
			free(*split_line);
			split_line++;
		}
		free(*split_line);
		free(*s);
		*s = NULL;
	}
}

void	cub_parsing_fetch_data(t_global *g, int fd, int *checks)
{
	while (get_next_line(fd, &g->line) > 0)
	{
		g->split = ft_split(g->line, ' ');
		if (g->split[0] == NULL)
			cub_parsing_free_split(&(g->split), &(g->line));
		else if (cub_parsing_get_array_len(g->split) != 2)
			cub_error_str(g, MERR_PARAM_INVALID);
		else if (!cub_parsing_strcmp("NO", g->split[0]))
			cub_parsing_fill_path(g, &(g->d.n), checks);
		else if (!cub_parsing_strcmp("SO", g->split[0]))
			cub_parsing_fill_path(g, &(g->d.s), checks);
		else if (!cub_parsing_strcmp("EA", g->split[0]))
			cub_parsing_fill_path(g, &(g->d.e), checks);
		else if (!cub_parsing_strcmp("WE", g->split[0]))
			cub_parsing_fill_path(g, &(g->d.w), checks);
		else if (!cub_parsing_strcmp("C", g->split[0]))
			cub_parsing_fill_color(g, &(g->d.c), checks);
		else if (!cub_parsing_strcmp("F", g->split[0]))
			cub_parsing_fill_color(g, &(g->d.f), checks);
		else
			cub_error_str(g, MERR_PARAM_INVALID);
		cub_parsing_free_split(&(g->split), &(g->line));
		if (*checks == 0)
			break ;
	}
}
